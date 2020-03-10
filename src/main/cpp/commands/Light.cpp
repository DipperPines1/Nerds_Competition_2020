/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Light.h"
#include "subsystems/Launcher.h"
#include "nerds/Preferences.h"

Light::Light(Launcher* launcher) :
  launcher_(launcher) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void Light::Initialize() {
  launcher_->SetLight(true);
}

// Called repeatedly when this Command is scheduled to run
void Light::Execute() {}

// Called once the command ends or is interrupted.
void Light::End(bool interrupted) {
  launcher_->SetLight(false);
}

// Returns true when the command should end.
bool Light::IsFinished() { return false; }