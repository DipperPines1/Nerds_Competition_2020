/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveJoystick.h"

#include <cmath>

#include "Config.h"
#include "Constants.h"
#include "nerds/Preferences.h"
#include "Robot.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/OI.h"

DriveJoystick::DriveJoystick(Drivetrain* drivetrain, OI* oi)
  : drivetrain_(drivetrain),
    oi_(oi) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivetrain_, oi_});

  drive_max_speed_ = new double(0);
  drive_min_speed_ = new double(0);
  turn_max_speed_ = new double(0);
  turn_min_speed_ = new double (0);
  drive_deadzone_ = new double(0);
  reverse_forward_ = new bool(0);

  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_DRIVE_MAX.key,
    drive_max_speed_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_DRIVE_MIN.key,
    drive_min_speed_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICKS_TURN_MAX.key,
    turn_max_speed_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICKS_TURN_MIN.key,
    turn_min_speed_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICKS_DRIVE_DEADZONE.key,
    drive_deadzone_);
  nerd::Preferences::GetInstance().AddListener<bool>(
    JOYSTICKS_REVERSE_FORWARD.key,
    reverse_forward_);
}

// Called when the command is initially scheduled.
void DriveJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveJoystick::Execute() {
  double speed = -ApplyDeadzone(DriveJoystick::oi_->GetAxis(AXIS_LEFT_Y),
    *drive_deadzone_);
  double turn = ApplyDeadzone(DriveJoystick::oi_->GetAxis(AXIS_RIGHT_X),
    *drive_deadzone_);

  if (*reverse_forward_) {
    speed *= -1;
  }

  drivetrain_->ArcadeDrive(
    DriveProfile(speed, *drive_min_speed_, *drive_max_speed_),
    DriveProfile(turn, *turn_min_speed_, *turn_max_speed_),
    false);
}

// Called once the command ends or is interrupted.
void DriveJoystick::End(bool interrupted) {
  drivetrain_->ArcadeDrive(0, 0, false);
}

// Returns true when the command should end.
bool DriveJoystick::IsFinished() {
  return false;
}

double DriveJoystick::DriveProfile(double input, double min, double max) {
  if (input == 0) {
    return 0;
  }

  double slope = max-min;
  double output = slope *std::pow(std::abs(input), 2) + min;

  if (input < 0) {
    output *=-1;
  }

  return output;
}

double DriveJoystick::ApplyDeadzone(double input, double deadzone) {
  if (std::abs(input) < std::abs(deadzone)) {
    return 0;
  }

  return input;
}
