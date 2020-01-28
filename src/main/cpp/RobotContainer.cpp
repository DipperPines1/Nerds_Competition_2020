/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
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

RobotContainer::RobotContainer()
  : drivetrain_(),
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
}
frc2::Command* RobotContainer::GetAutonomousCommand() {
  return nullptr;
}


void RobotContainer::DriveThroughPath(std::vector<frc::Translation2d> waypoints, frc::Pose2d end_pose) {
  auto path = frc::TrajectoryGenerator::GenerateTrajectory(
    drivetrain.GetPose(),
    waypoints,
    end_pose,
    drivetrain.GetTrajectoryConfig());

  autonomous_drive.reset(new frc2::RamseteCommand(
    path,
    [this]() {
      return drivetrain.GetPose();
    },
    frc::RamseteController(K_RAMSETE_B, K_RAMSETE_ZETA),
    frc::SimpleMotorFeedforward<units::meters>(KS, KV, KA),
    drivetrain.GetDriveKinematics(),
    [this] {
      return drivetrain.WheelSpeed();
    },
    frc2::PIDController(KP_DRIVE_VELOCITY, 0.0, 0.0),
    frc2::PIDController(KP_DRIVE_VELOCITY, 0.0, 0.0),
    [this](auto left, auto right) {
      drivetrain.TankDriveVolts(left, right);
    },
    {&drivetrain}));

  frc::SmartDashboard::PutData("Commands/Ramsete", autonomous_drive.get());
}

void RobotContainer::StopAutoDrive() {
  autonomous_drive->Cancel();
}
  
frc::Pose2d RobotContainer::GetPose() {
  return drivetrain.GetPose();
}