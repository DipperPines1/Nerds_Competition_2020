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
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
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

  double* drive_max_speed_;
  double* drive_min_speed_;
  double* turn_max_speed_;
  double* turn_min_speed_;
  double* drive_deadzone_;
  bool* reverse_forward_;

  double driveProfile(double, double, double);
  double applyDeadzone(double, double);
};
