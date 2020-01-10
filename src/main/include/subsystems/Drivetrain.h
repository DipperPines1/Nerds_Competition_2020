/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/VictorSP.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>


class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /**
   * @brief Move the robot using an arcade drive control scheme.
   * 
   * @param speed The forward/backwards speed.
   * 
   * @param turn The rate at which the robot turns.
   * 
   * @param squared If true, inputs are squared.
   */
  void ArcadeDrive(double speed, double turn, bool squared);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::VictorSP front_left;
  frc::VictorSP front_right;
  frc::VictorSP back_left;
  frc::VictorSP back_right;

  frc::SpeedControllerGroup left_;
  frc::SpeedControllerGroup right_;

  frc::DifferentialDrive drive_;
};
