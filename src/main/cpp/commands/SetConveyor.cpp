/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetConveyor.h"

#include "Config.h"
#include "nerds/Preferences.h"
#include "subsystems/Launcher.h"

SetConveyor::SetConveyor(bool reverse, Launcher* launcher) :
  launcher_(launcher),
  reverse_(reverse) {
  // Use addRequirements() here to declare subsystem dependencies.
  // AddRequirements({launcher_});
}

// Called when the command is initially scheduled.
void SetConveyor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetConveyor::Execute() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONVEYOR_SPEED.key,
    LAUNCHER_CONVEYOR_SPEED.value);

  if (reverse_) {
    launcher_->RunConveyor(speed);
  } else {
    launcher_->RunConveyor(-speed);
  }

}

// Called once the command ends or is interrupted.
void SetConveyor::End(bool interrupted) {
  launcher_->RunConveyor(0);
}

// Returns true when the command should end.
bool SetConveyor::IsFinished() { return false; }
