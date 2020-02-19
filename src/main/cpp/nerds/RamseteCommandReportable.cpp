/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "nerds/RamseteCommandReportable.h"

#include <units/units.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace nerd;

RamseteCommandReportable::RamseteCommandReportable(
  frc::Trajectory trajectory,
  std::function< frc::Pose2d()> pose,
  frc::RamseteController controller,
  frc::SimpleMotorFeedforward< units::meters > feedforward,
  frc::DifferentialDriveKinematics kinematics,
  std::function< frc::DifferentialDriveWheelSpeeds()> wheelSpeeds,
  frc2::PIDController leftController,
  frc2::PIDController rightController,
  std::function< void(units::volt_t, units::volt_t)> output,
  std::initializer_list< frc2::Subsystem * > requirements)
    : frc2::RamseteCommand(
        trajectory,
        pose,
        controller,
        feedforward,
        kinematics,
        wheelSpeeds,
        leftController,
        rightController,
        output,
        requirements),
      left_PID_(leftController),
      right_PID_(rightController) {}


RamseteCommandReportable::RamseteCommandReportable(
  frc::Trajectory trajectory,
  std::function< frc::Pose2d()> pose,
  frc::RamseteController controller,
  frc::SimpleMotorFeedforward< units::meters > feedforward,
  frc::DifferentialDriveKinematics kinematics,
  std::function< frc::DifferentialDriveWheelSpeeds()> wheelSpeeds,
  frc2::PIDController leftController,
  frc2::PIDController rightController,
  std::function< void(units::volt_t, units::volt_t)> output,
  wpi::ArrayRef< frc2::Subsystem * > requirements)
    : frc2::RamseteCommand(
      trajectory,
      pose,
      controller,
      feedforward,
      kinematics,
      wheelSpeeds,
      leftController,
      rightController,
      output,
      requirements),
    left_PID_(leftController),
    right_PID_(rightController) {}

void RamseteCommandReportable::Execute() {
  double left_output = left_PID_.GetVelocityError();
  double right_output = right_PID_.GetVelocityError();

  frc::SmartDashboard::PutNumber(
    "PID Controllers/Left Velocity Error",
    left_output);
  frc::SmartDashboard::PutNumber(
    "PID Controllers/Right Velocity Error",
    right_output);

  frc2::RamseteCommand::Execute();
}
