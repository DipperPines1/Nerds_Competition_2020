/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc2/command/button/JoystickButton.h>
#include <frc/Joystick.h>



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

  /**
   * @brief Binds a command to a button
   * 
   * @param button The button which the command will be bound to
   * 
   * @param command The command which will run when the button is pressed
   */
  void BindCommandButton(int button, frc2::Command* command);
  void BindCommandTrigger(int trigger, frc2::Command* command);

 private:
  frc::Joystick driver_;
  frc2::JoystickButton driver_A_;
  frc2::JoystickButton driver_B_;
  frc2::JoystickButton driver_X_;
  frc2::JoystickButton driver_Y_;
  frc2::JoystickButton driver_LB_;
  frc2::JoystickButton driver_RB_;
  frc2::Button trigger_left_;
  frc2::Button trigger_right_;

  std::vector<frc2::Command*> bound_commands_;
};
