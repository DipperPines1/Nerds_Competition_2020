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
    JOYSTICK_DRIVE_MAX_HIGH.key,
    JOYSTICK_DRIVE_MAX_HIGH.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_DRIVE_MAX_LOW.key,
    JOYSTICK_DRIVE_MAX_LOW.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_DRIVE_MIN_HIGH.key,
    JOYSTICK_DRIVE_MIN_HIGH.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_DRIVE_MIN_LOW.key,
    JOYSTICK_DRIVE_MIN_LOW.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_TURN_MAX_HIGH.key,
    JOYSTICK_TURN_MAX_HIGH.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_TURN_MAX_LOW.key,
    JOYSTICK_TURN_MAX_LOW.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_TURN_MIN_HIGH.key,
    JOYSTICK_TURN_MIN_HIGH.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICK_TURN_MIN_LOW.key,
    JOYSTICK_TURN_MIN_LOW.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICKS_DRIVE_DEADZONE.key,
    JOYSTICKS_DRIVE_DEADZONE.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    JOYSTICKS_REVERSE_FORWARD.key,
    JOYSTICKS_REVERSE_FORWARD.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    SWITCH_SPEED_PREFERENCES.key,
    SWITCH_SPEED_PREFERENCES.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_CONTROLLER_P.key,
    LAUNCHER_CONTROLLER_P.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_CONTROLLER_I.key,
    LAUNCHER_CONTROLLER_I.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_CONTROLLER_D.key,
    LAUNCHER_CONTROLLER_D.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_MAX_SPEED.key,
    LAUNCHER_MAX_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_MIN_SPEED.key,
    LAUNCHER_MIN_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_CURRENT_SPEED.key,
    LAUNCHER_CURRENT_SPEED.value,
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

bool ApplyConfig::RunsWhenDisabled() {
  return true;
}
