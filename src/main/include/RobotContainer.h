/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include <memory>
#include <frc/trajectory/Trajectory.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>

#include "commands/ApplyConfig.h"
#include "commands/DriveJoystick.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/OI.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

  /**
   * @brief Automatically schedule the robot to drive through the specified path
   * 
   * @param path The path the robot will attempt to automatically drive through
   */
  void DriveThroughPath(frc::Pose2d initial_pose, std::vector<frc::Translation2d> waypoints, frc::Pose2d end_pose);

  /**
   * @brief Stop the robot's current autonomous driving command
   * 
   */
  void StopAutoDrive();

  /**
   * @brief Get the Pose object
   * 
   * @return frc::Pose2d 
   */
  frc::Pose2d GetPose();

  /**
   * @brief Creates a Voltage Constraint for auto
   * 
   * @return frc::DifferentialDriveVoltageConstraint 
   */
  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint();
  
 private:
  void SetupListeners();

  Drivetrain drivetrain_;
  OI oi_;

  ApplyConfig apply_config_;
  DriveJoystick drive_joy_;

  std::shared_ptr<frc2::RamseteCommand> autonomous_drive;

  // Ramsete Listener Pointers
  double* feed_forward_ks_;
  double* feed_forward_ka_;
  double* feed_forward_kv_;
  double* kp_drive_velocity_;
  double* k_max_speed_;
  double* k_max_acceleration_;
  double* k_ramsete_b_;
  double* k_ramsete_zeta_;
  double* ramsete_max_speed_;
  double* ramsete_min_speed_;

  void ConfigureButtonBindings();
};
