/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/VictorSP.h>


class Climber : public frc2::SubsystemBase {
 public:
  Climber();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /**
   * @brief Make the extender extend or retract
   * 
   * @param extended If true, extend the extender
   */
  void SetExtender(bool extended);

  /**
   * @brief Get the current settings of the extender
   * 
   * @return true The extender is extended
   * @return false The extender is retracted
   */
  bool GetExtender();

  /**
   * @brief Set reeling speed
   * 
   * @param speed the speed which the motor runs at
   */
  void SetReelSpeed(double speed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::DoubleSolenoid extender_;
  frc::VictorSP reel_;
};
