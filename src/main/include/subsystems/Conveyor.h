/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/VictorSP.h>



class Conveyor : public frc2::SubsystemBase {
 public:
  Conveyor();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void RunConveyor(double speed);

  bool IsBallDetected();
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::VictorSP conveyor_;
  frc::DigitalInput ball_sensor_;

  bool* feed_override_;
};
