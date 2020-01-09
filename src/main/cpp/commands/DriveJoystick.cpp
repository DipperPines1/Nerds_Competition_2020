/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveJoystick.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/OI.h"
#include "Constants.h"

DriveJoystick::DriveJoystick(Drivetrain* drivetrain, OI* oi)
  : drivetrain_(drivetrain),
    oi_(oi) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivetrain_, oi_});
}

// Called when the command is initially scheduled.
void DriveJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveJoystick::Execute() {
  double speed = oi_->GetAxis(AXIS_LEFT_Y);
  double turn = oi_->GetAxis(AXIS_LEFT_X);
  drivetrain_->ArcadeDrive(speed, turn, false);
}

// Called once the command ends or is interrupted.
void DriveJoystick::End(bool interrupted) {
  drivetrain_->ArcadeDrive(0, 0, false);
}

// Returns true when the command should end.
bool DriveJoystick::IsFinished() {
  return false;
}
