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
#include <frc/controller/PIDController.h>
#include <units/units.h>

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
  // Create a voltage constraint to ensure we don't accelerate too fast
  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
      frc::SimpleMotorFeedforward<units::inch_t>(KS, KV, KA),
      K_DRIVE_KINEMATICS,
      10);

  // Set up config for trajectory
  frc::TrajectoryConfig config(
    K_MAX_SPEED,
    K_MAX_ACCELERATION);

  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(K_DRIVE_KINEMATICS);

  // Apply the voltage constraint
  config.AddConstraint(autoVoltageConstraint);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0, 0, frc::Rotation2d(0)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1, 1), frc::Translation2d(2, -1)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3, 0, frc::Rotation2d(0)), config);

  frc2::RamseteCommand* ramseteCommand(
      exampleTrajectory, [this]() {
        return drivetrain.GetPose();
      },
      frc::RamseteController(kRamseteB, kRamseteZeta),
      frc::SimpleMotorFeedforward<>(
        KS, KV, KA),
        K_DRIVE_KINEMATICS,
      [this] {
        return drivetrain.GetWheelSpeeds();
      },
      frc::PIDController(KP_DRIVE_VELOCITY, 0, 0),
      frc::PIDController(KP_DRIVE_VELOCITY, 0, 0),
      [this](auto left, auto right) {
        drivetrain.TankDriveVolts(left, right);
      },
      {&drivetrain});

  return ramseteCommand;
}