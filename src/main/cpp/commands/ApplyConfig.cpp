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

  // Launcher
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
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_CONVEYOR_SPEED.key,
    LAUNCHER_CONVEYOR_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    LAUNCHER_INTAKE_SPEED.key,
    LAUNCHER_INTAKE_SPEED.value,
    false);
  // End Launcher

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
  nerd::Preferences::GetInstance().AddPreference(
    SET_REEL_SPEED.key,
    SET_REEL_SPEED.value,
    false);
  // Ramsete
  nerd::Preferences::GetInstance().AddPreference(
    FEEDFORWARD_KS.key,
    FEEDFORWARD_KS.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    FEEDFORWARD_KA.key,
    FEEDFORWARD_KA.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    FEEDFORWARD_KV.key,
    FEEDFORWARD_KV.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    KP_DRIVE_VELOCITY.key,
    KP_DRIVE_VELOCITY.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    K_MAX_SPEED.key,
    K_MAX_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    K_MAX_ACCELERATION.key,
    K_MAX_ACCELERATION.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    K_RAMSETE_B.key,
    K_RAMSETE_B.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    K_RAMSETE_ZETA.key,
    K_RAMSETE_ZETA.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    RAMSETE_DRIVE_MAX_SPEED.key,
    RAMSETE_DRIVE_MAX_SPEED.value,
    false);
  nerd::Preferences::GetInstance().AddPreference(
    RAMSETE_DRIVE_MIN_SPEED.key,
    RAMSETE_DRIVE_MIN_SPEED.value,
    false);
  // end Ramsete
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
