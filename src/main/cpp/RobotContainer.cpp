/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/geometry/Pose2D.h>
#include <frc/geometry/Rotation2D.h>
#include <frc/geometry/Translation2D.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/PIDController.h>
#include <units/units.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Constants.h"
#include "commands/SpeedSwitch.h"
#include "Config.h"
#include "nerds/Preferences.h"

RobotContainer::RobotContainer()
  : drivetrain_(),
    oi_(),
    apply_config_(),
    drive_joy_(&drivetrain_, &oi_) {
  ConfigureButtonBindings();
  SetupListeners();
  
  // Set default commands
  drivetrain_.SetDefaultCommand(drive_joy_);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Commands/Load Config", &apply_config_);

  oi_.BindCommandButton(BUTTON_A, new SpeedSwitch());
}
frc2::Command* RobotContainer::GetAutonomousCommand() {
  return nullptr;
}


void RobotContainer::DriveThroughPath(
    frc::Pose2d initial_pose,
    std::vector<frc::Translation2d> waypoints,
    frc::Pose2d end_pose) {
  frc::RamseteController controller(
    *k_ramsete_b_,
    *k_ramsete_zeta_);

  auto ks = *feed_forward_ks_ * 1_V;
  auto kv = *feed_forward_kv_ * 1_V * 1_s / 1_m;
  auto ka = *feed_forward_ka_ * 1_V * 1_s * 1_s / 1_m;

  frc::SimpleMotorFeedforward<units::meters> feed_forward(ks, kv, ka);

  auto max_speed = *k_max_speed_ * 1_mps;
  auto max_acceleration = *k_max_acceleration_ * 1_mps_sq;

  frc::TrajectoryConfig trajectory_config(
    max_speed,
    max_acceleration);

  frc::DifferentialDriveKinematics kinematics(K_TRACK_WIDTH);

  trajectory_config.SetKinematics(kinematics);

  auto path = frc::TrajectoryGenerator::GenerateTrajectory(
    initial_pose,
    waypoints,
    end_pose,
    trajectory_config);

  double max = *ramsete_max_speed_;
  double min = *ramsete_min_speed_;

  autonomous_drive.reset(new frc2::RamseteCommand(
    path,
    [this]() {
      return drivetrain_.GetPose();
    },
    controller,
    feed_forward,
    kinematics,
    [this] {
      return drivetrain_.WheelSpeed();
    },
    frc2::PIDController(*kp_drive_velocity_, 0.0, 0.0),
    frc2::PIDController(*kp_drive_velocity_, 0.0, 0.0),
    [this, max, min](units::volt_t left, units::volt_t right) {
      double left_input = left.to<double>()/12;
      double right_input = right.to<double>()/12;

      double left_speed = (max - min) * std::fabs(left_input) + min;
      double right_speed = (max - min) * std::fabs(right_input) + min;

      if (left_speed > max) {
          left_speed = max;
      }
      if (right_speed > max) {
          right_speed = max;
      }

      left_speed *= left_input > 0 ? 1 : -1;
      right_speed *= right_input > 0 ? 1 : -1;

      frc::SmartDashboard::PutNumber("Ramsete/left", left.to<double>());
      frc::SmartDashboard::PutNumber("Ramsete/right", right.to<double>());
      drivetrain_.TankDrive(left_speed, right_speed);
    },
    {&drivetrain_}));

  frc::SmartDashboard::PutData("Commands/Ramsete", autonomous_drive.get());
  oi_.BindCommandButton(BUTTON_B, autonomous_drive.get());
}

void RobotContainer::StopAutoDrive() {
  autonomous_drive->Cancel();
}

frc::Pose2d RobotContainer::GetPose() {
  return drivetrain_.GetPose();
}

void RobotContainer::SetupListeners() {
  feed_forward_ks_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    FEEDFORWARD_KS.key,
    feed_forward_ks_);
  feed_forward_ka_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    FEEDFORWARD_KA.key,
    feed_forward_ka_);
  feed_forward_kv_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    FEEDFORWARD_KV.key,
    feed_forward_kv_);
  kp_drive_velocity_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    KP_DRIVE_VELOCITY.key,
    kp_drive_velocity_);
  k_max_speed_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    K_MAX_SPEED.key,
    k_max_speed_);
  k_max_acceleration_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    K_MAX_ACCELERATION.key,
    k_max_acceleration_);
  k_ramsete_b_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    K_RAMSETE_B.key,
    k_ramsete_b_);
  k_ramsete_zeta_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    K_RAMSETE_ZETA.key,
    k_ramsete_zeta_);
  ramsete_max_speed_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    RAMSETE_DRIVE_MAX_SPEED.key,
    ramsete_max_speed_);
  ramsete_min_speed_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
    RAMSETE_DRIVE_MIN_SPEED.key,
    ramsete_min_speed_);
}