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
  // Joysticks
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
  // End Joysticks

  // Autonomous PID
  nerd::Preferences::GetInstance().AddPreference(
    AUTO_TURN_P.key,
    AUTO_TURN_P.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTO_TURN_I.key,
    AUTO_TURN_I.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTO_TURN_D.key,
    AUTO_TURN_D.value,
    false);
  // End Autonomous PID

  // Autonomous Preferences
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_DRIVE_TOLERANCE.key,
    AUTONOMOUS_DRIVE_TOLERANCE.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_DRIVE_ACCELERATION.key,
    AUTONOMOUS_DRIVE_ACCELERATION.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_DRIVE_MAX_SPEED.key,
    AUTONOMOUS_DRIVE_MAX_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_DRIVE_MIN_SPEED.key,
    AUTONOMOUS_DRIVE_MIN_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_TURN_TOLERANCE.key,
    AUTONOMOUS_TURN_TOLERANCE.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_TURN_MAX_SPEED.key,
    AUTONOMOUS_TURN_MAX_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_TURN_MIN_SPEED.key,
    AUTONOMOUS_TURN_MIN_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    AUTONOMOUS_TURN_TIME_ON_TARGET.key,
    AUTONOMOUS_TURN_TIME_ON_TARGET.value,
    false);
  // End Autonomous Parameters
  
  // Start Vision Parameters
    nerd::Preferences::GetInstance().AddPreference(
      VISION_TURN_MAX_SPEED.key,
      VISION_TURN_MAX_SPEED.value,
      false); 
    nerd::Preferences::GetInstance().AddPreference(
      VISION_TURN_MIN_SPEED.key,
      VISION_TURN_MIN_SPEED.value,
      false); 
    nerd::Preferences::GetInstance().AddPreference(
      VISION_TOLERANCE.key,
      VISION_TOLERANCE.value,
      false); 
    nerd::Preferences::GetInstance().AddPreference(
      VISION_PID_P.key,
      VISION_PID_P.value,
      false);
    nerd::Preferences::GetInstance().AddPreference(
      VISION_PID_I.key,
      VISION_PID_I.value,
      false);
    nerd::Preferences::GetInstance().AddPreference(
      VISION_PID_D.key,
      VISION_PID_D.value,
      false);
    nerd::Preferences::GetInstance().AddPreference(
      PID_TIME_ON_TARGET.key,
      PID_TIME_ON_TARGET.value,
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
