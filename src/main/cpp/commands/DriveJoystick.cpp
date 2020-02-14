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
  AddRequirements({drivetrain_});

  drive_max_speed_high_ = new double(0);
  drive_max_speed_low_ = new double(0);
  drive_min_speed_high_ = new double(0);
  drive_min_speed_low_ = new double(0);
  turn_max_speed_high_ = new double(0);
  turn_max_speed_low_ = new double(0);
  turn_min_speed_high_ = new double (0);
  turn_min_speed_low_ = new double(0);
  drive_deadzone_ = new double(0);
  reverse_forward_ = new bool(false);
  low_speed_switch_ = new bool(false);

  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICKS_DRIVE_DEADZONE.key,
    drive_deadzone_);
  nerd::Preferences::GetInstance().AddListener<bool>(
    JOYSTICKS_REVERSE_FORWARD.key,
    reverse_forward_);
  nerd::Preferences::GetInstance().AddListener<bool>(
    SWITCH_SPEED_PREFERENCES.key,
    low_speed_switch_
  );

  //high listeners
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_DRIVE_MAX_HIGH.key,
    drive_max_speed_high_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_DRIVE_MIN_HIGH.key,
    drive_min_speed_high_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_TURN_MAX_HIGH.key,
    turn_max_speed_high_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_TURN_MIN_HIGH.key,
    turn_min_speed_high_);

  // low listeners
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_DRIVE_MAX_LOW.key,
    drive_max_speed_low_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_DRIVE_MIN_LOW.key,
    drive_min_speed_low_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_TURN_MAX_LOW.key,
    turn_max_speed_low_);
  nerd::Preferences::GetInstance().AddListener<double>(
    JOYSTICK_TURN_MIN_LOW.key,
    turn_min_speed_low_);
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

  double speed_max = *drive_max_speed_high_;
  double speed_min = *drive_min_speed_high_;
  double turn_max = *turn_max_speed_high_;
  double turn_min = *turn_min_speed_high_;

  if (*low_speed_switch_) {
    speed_max = *drive_max_speed_low_;
    speed_min = *drive_min_speed_low_;
    turn_max = *turn_max_speed_low_;
    turn_min = *turn_min_speed_low_;
  }

  drivetrain_->ArcadeDrive(
    DriveProfile(speed, speed_min, speed_max),
    DriveProfile(turn, turn_min, turn_max),
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
