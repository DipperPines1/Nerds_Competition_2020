/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SpeedSwitch.h"

#include "Config.h"
#include "nerds/Preferences.h"

SpeedSwitch::SpeedSwitch() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SpeedSwitch::Initialize() {
  bool switch_speed = nerd::Preferences::GetInstance().GetPreference<bool>(SWITCH_SPEED_PREFERENCES.key, SWITCH_SPEED_PREFERENCES.value);

  nerd::Preferences::GetInstance().AddPreference(SWITCH_SPEED_PREFERENCES.key, !switch_speed, true);
}

// Called repeatedly when this Command is scheduled to run
void SpeedSwitch::Execute() {

}

// Called once the command ends or is interrupted.
void SpeedSwitch::End(bool interrupted) {}

// Returns true when the command should end.
bool SpeedSwitch::IsFinished() { return true; }
