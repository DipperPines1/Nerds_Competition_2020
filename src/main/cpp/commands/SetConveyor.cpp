/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetConveyor.h"

#include "Config.h"
#include "nerds/Preferences.h"
#include "subsystems/Conveyor.h"

SetConveyor::SetConveyor(bool reverse, Conveyor* conveyor) :
  conveyor_(conveyor),
  reverse_(reverse) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({conveyor_});
}

// Called when the command is initially scheduled.
void SetConveyor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetConveyor::Execute() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONVEYOR_SPEED.key,
    LAUNCHER_CONVEYOR_SPEED.value);

  if (reverse_) {
    conveyor_->RunConveyor(speed);
  } else {
    conveyor_->RunConveyor(-speed);
  }
}

// Called once the command ends or is interrupted.
void SetConveyor::End(bool interrupted) {
  conveyor_->RunConveyor(0);
}

// Returns true when the command should end.
bool SetConveyor::IsFinished() { return false; }
