/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

class Launcher : public frc2::SubsystemBase {
 public:
  Launcher();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SetLauncherSpeed(double speed);

  double GetLauncherSpeed();

 private:
  void SetupListeners();

  rev::CANSparkMax shooter_;
};
