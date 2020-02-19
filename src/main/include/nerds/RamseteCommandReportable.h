/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/RamseteCommand.h>
#include <frc/PIDController.h>
#include <units/units.h>
#include <frc/geometry/Pose2D.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/controller/RamseteController.h>
#include <frc2/command/Subsystem.h>

namespace nerd {

class RamseteCommandReportable : public frc2::RamseteCommand {
 public:
  RamseteCommandReportable(
    frc::Trajectory trajectory,
    std::function< frc::Pose2d()> pose,
    frc::RamseteController controller,
    frc::SimpleMotorFeedforward< units::meters > feedforward,
    frc::DifferentialDriveKinematics kinematics,
    std::function< frc::DifferentialDriveWheelSpeeds()> wheelSpeeds,
    frc2::PIDController leftController,
    frc2::PIDController rightController,
    std::function< void(units::volt_t, units::volt_t)> output,
    std::initializer_list< frc2::Subsystem * > requirements);

  RamseteCommandReportable(
    frc::Trajectory trajectory,
    std::function< frc::Pose2d()> pose,
    frc::RamseteController controller,
    frc::SimpleMotorFeedforward< units::meters > feedforward,
    frc::DifferentialDriveKinematics kinematics,
    std::function< frc::DifferentialDriveWheelSpeeds()> wheelSpeeds,
    frc2::PIDController leftController,
    frc2::PIDController rightController,
    std::function< void(units::volt_t, units::volt_t)> output,
    wpi::ArrayRef< frc2::Subsystem * > requirements = {});

  void Execute() override;

 private:
  frc2::PIDController left_PID_;
  frc2::PIDController right_PID_;
};

}  // namespace nerd
