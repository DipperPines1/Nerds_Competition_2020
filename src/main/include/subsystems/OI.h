/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>



class OI : public frc2::SubsystemBase {
 public:
  OI();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /**
   * @brief Get the Axis value
   * 
   * @param axis The selected axis on the joystick.
   * 
   * @return double The value of the selected axis.
   */
  double GetAxis(int axis);

 private:
  frc::Joystick driver_;
  frc2::JoystickButton driver_A_;
};
