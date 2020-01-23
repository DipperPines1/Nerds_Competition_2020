/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/units.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>

#include "Constants.h"

void Robot::RobotInit() {}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  std::cout << "I got this far" << std::endl;
  frc::TrajectoryConfig config(
  K_MAX_SPEED,
  K_MAX_ACCELERATION);

  config.SetKinematics(K_DRIVE_KINEMATICS);

  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
  frc::SimpleMotorFeedforward<units::meters>(KS, KV, KA),
  K_DRIVE_KINEMATICS,
  10_V);

  config.AddConstraint(autoVoltageConstraint);

  std::vector<frc::Translation2d> waypoints{{1_m, 1_m}};
  frc::Pose2d initialPose(0_m, 0_m, 0_rad);
  frc::Pose2d endPose(1_m, 2_m, 0_rad);

  std::cout << "I got this far 2" << std::endl;

  frc::Trajectory path = frc::TrajectoryGenerator::GenerateTrajectory(
    initialPose,
    waypoints,
    endPose,
    config);

  std::cout << "I got this far 3" << std::endl;

  m_container.DriveThroughPath(path);
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
