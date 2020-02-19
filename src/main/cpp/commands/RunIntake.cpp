/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunIntake.h"

#include "Config.h"
#include "nerds/Preferences.h"
#include "subsystems/Intake.h"

RunIntake::RunIntake(bool reverse, Intake* intake) :
  intake_(intake),
  reverse_(reverse) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({intake_});
}

// Called when the command is initially scheduled.
void RunIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntake::Execute() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_INTAKE_SPEED.key,
    LAUNCHER_INTAKE_SPEED.value);

  if (reverse_) {
    intake_->RunIntake(-speed);
  } else {
    intake_->RunIntake(speed);
  }
}

// Called once the command ends or is interrupted.
void RunIntake::End(bool interrupted) {
  intake_->RunIntake(0);
}

// Returns true when the command should end.
bool RunIntake::IsFinished() { return false; }
