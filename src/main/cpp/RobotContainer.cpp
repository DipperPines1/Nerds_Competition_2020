/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/controller/RamseteController.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "Constants.h"
#include "commands/RunIntake.h"
#include "commands/SetLauncher.h"
#include "commands/SetConveyor.h"
#include "commands/SetReelSpeed.h"
#include "commands/SpeedSwitch.h"
#include "commands/ToggleExtender.h"
#include "commands/ToggleStopper.h"


RobotContainer::RobotContainer()
  : drivetrain_(),
    launcher_(),
    climber_(),
    oi_(),
    apply_config_(),
    drive_joy_(&drivetrain_, &oi_) {
  ConfigureButtonBindings();

  // Set default commands
  drivetrain_.SetDefaultCommand(drive_joy_);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Commands/Load Config", &apply_config_);

  oi_.BindCommandButton(BUTTON_A, new SpeedSwitch());
  oi_.BindCommandButton(BUTTON_X, new ToggleExtender(&climber_));
  oi_.BindCommandButton(BUTTON_LB, new RunIntake(false, &launcher_));
  oi_.BindCommandButton(BUTTON_RB, new RunIntake(true, &launcher_));

  oi_.BindCommandTrigger(TRIGGER_RIGHT, new SetLauncher(&launcher_));
  oi_.BindCommandTrigger(TRIGGER_LEFT, new SetConveyor(false, &launcher_));
  oi_.BindCommandTrigger(DPAD_LEFT, new SetConveyor(true, &launcher_));
  oi_.BindCommandButton(BUTTON_Y, new SetReelSpeed(&climber_));
  oi_.BindCommandButton(BUTTON_B, new ToggleStopper(&climber_));
}
frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  auto ks = *feed_forward_ks_ * 1_V;
  auto kv = *feed_forward_kv_ * 1_V * 1_s / 1_m;;
  auto ka = *feed_forward_ka_ * 1_V * 1_s * 1_s / 1_m;

  frc::DifferentialDriveKinematics kinematics(TRACK_WIDTH);

  frc::DifferentialDriveVoltageConstraint voltage_constraint(
    frc::SimpleMotorFeedforward<units::meters>(
      ks,
      kv,
      ka),
    kinematics,
    10_V);
  
  double max_speed = *k_max_speed_;
  double max_acceleration = *k_max_acceleration_;
  frc::TrajectoryConfig config{
    units::meters_per_second_t(max_speed),
    units::meters_per_second_squared_t(max_acceleration)};

  config.SetKinematics(kinematics);

  config.AddConstraint(voltage_constraint);

  frc::Pose2d initial_pose(0_m, 0_m, frc::Rotation2d(0_deg));
  frc::Pose2d end_pose(3_m, 0_m, frc::Rotation2d(0_deg));

  auto path = frc::TrajectoryGenerator::GenerateTrajectory(
    // Start at the origin facing the +X direction
    initial_pose,
    // Pass through these two interior waypoints, making an 's' curve path
    {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
    // End 3 meters straight ahead of where we started, facing forward
    end_pose,
    // Pass the config
    config);

  frc::Transform2d transform = drivetrain_.GetPose() - initial_pose;
  path = path.TransformBy(transform);

  frc2::RamseteCommand ramsete(
    path,
    [this]() { return drivetrain_.GetPose(); },
    frc::RamseteController(*k_ramsete_b_, *k_ramsete_zeta_),
    frc::SimpleMotorFeedforward<units::meters>(
      units::volt_t(ks),
      units::meters_per_second_t(kv),
      units::meters_per_second_squared_t(ka)),
    kinematics,
    [this] { return drivetrain_.GetWheelSpeed(); },
    frc2::PIDController(*kp_drive_velocity_, 0, 0),
    frc2::PIDController(*kp_drive_velocity_, 0, 0),
    [this](auto left, auto right) { drivetrain_.TankDriveVolts(left, right); },
    {&drivetrain_});

  return new frc2::SequentialCommandGroup(
    std::move(ramsete),
    frc2::InstantCommand([this] { drivetrain_.TankDriveVolts(0_V, 0_V); }, {}));
}
