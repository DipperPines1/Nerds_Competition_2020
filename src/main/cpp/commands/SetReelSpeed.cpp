/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetReelSpeed.h"

#include "Config.h"
#include "nerds/Preferences.h"
#include "subsystems/Climber.h"

SetReelSpeed::SetReelSpeed(Climber* climber) :
  climber_(climber) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({climber_});
}

// Called when the command is initially scheduled.
void SetReelSpeed::Initialize() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    SET_REEL_SPEED.key,
    SET_REEL_SPEED.value);
  climber_->SetReelSpeed(speed);
}

// Called repeatedly when this Command is scheduled to run
void SetReelSpeed::Execute() {}

// Called once the command ends or is interrupted.
void SetReelSpeed::End(bool interrupted) {}

// Returns true when the command should end.
bool SetReelSpeed::IsFinished() { return true; }
