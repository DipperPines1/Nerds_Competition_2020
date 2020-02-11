/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetLauncher.h"

#include "Config.h"
#include "nerds/Preferences.h"
#include "subsystems/Launcher.h"


SetLauncher::SetLauncher(Launcher* launcher) :
  launcher_(launcher)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({launcher});
}

// Called when the command is initially scheduled.
void SetLauncher::Initialize() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CURRENT_SPEED.key,
    LAUNCHER_CURRENT_SPEED.value);
  launcher_->SetLauncherSpeed(speed);
}

// Called repeatedly when this Command is scheduled to run
void SetLauncher::Execute() {}

// Called once the command ends or is interrupted.
void SetLauncher::End(bool interrupted) {}

// Returns true when the command should end.
bool SetLauncher::IsFinished() { return true; }
