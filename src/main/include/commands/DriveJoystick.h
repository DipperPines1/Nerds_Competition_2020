/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class Drivetrain;
class OI;

/**
 * @brief Allow the robot to be driven by Joystick 
 */
class DriveJoystick
    : public frc2::CommandHelper<frc2::CommandBase, DriveJoystick> {
 public:
  DriveJoystick(Drivetrain*, OI*);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drivetrain* drivetrain_;
  OI* oi_;

  double* drive_max_speed_high_;
  double* drive_max_speed_low_;
  double* drive_min_speed_high_;
  double* drive_min_speed_low_;
  double* turn_max_speed_high_;
  double* turn_max_speed_low_;
  double* turn_min_speed_high_;
  double* turn_min_speed_low_;
  double* drive_deadzone_;
  bool* reverse_forward_;
  bool* low_speed_switch_;

  double DriveProfile(double, double, double);
  double ApplyDeadzone(double, double);
};
