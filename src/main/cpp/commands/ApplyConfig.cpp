/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ApplyConfig.h"

#include "Config.h"
#include "nerds/Preferences.h"


ApplyConfig::ApplyConfig() {
}

// Called when the command is initially scheduled.
void ApplyConfig::Initialize() {
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_DRIVE_MAX.key,
    JOYSTICK_DRIVE_MAX.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_DRIVE_MIN.key,
    JOYSTICK_DRIVE_MIN.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICKS_TURN_MAX.key,
    JOYSTICKS_TURN_MAX.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICKS_TURN_MIN.key,
    JOYSTICKS_TURN_MIN.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICKS_DRIVE_DEADZONE.key,
    JOYSTICKS_DRIVE_DEADZONE.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICKS_REVERSE_FORWARD.key,
    JOYSTICKS_REVERSE_FORWARD.value,
    false);
}

// Called repeatedly when this Command is scheduled to run
void ApplyConfig::Execute() {}

// Called once the command ends or is interrupted.
void ApplyConfig::End(bool interrupted) {}

// Returns true when the command should end.
bool ApplyConfig::IsFinished() {
  return true;
}
