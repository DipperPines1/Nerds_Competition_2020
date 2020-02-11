/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignWithTarget.h"

#include <frc/SmartDashboard/SmartDashboard.h>
#include "Config.h"
#include "subsystems/Drivetrain.h"

AlignWithTarget::AlignWithTarget(Drivetrain* drivetrain)
  : drivetrain_(drivetrain)
{
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AlignWithTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AlignWithTarget::Execute() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);
  double Center_Y = frc::SmartDashboard::GetNumber(
    VISION_CENTER_Y.key,
    VISION_CENTER_Y.value);

  double turn;

  if (-50 < Center_X || Center_X < 50) {
    turn = 0;
  } else if (Center_X > 0) {
    turn = -0.5;
  } else if (Center_X < 0) {
    turn = 0.5;
  }
  drivetrain_->ArcadeDrive(0, turn, false);
}

// Called once the command ends or is interrupted.
void AlignWithTarget::End(bool interrupted) {
    drivetrain_->ArcadeDrive(0, 0, false);
}

// Returns true when the command should end.
bool AlignWithTarget::IsFinished() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);

  return -50 < Center_X || Center_X < 50; 
}
