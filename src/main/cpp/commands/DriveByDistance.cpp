/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveByDistance.h"

#include <algorithm>
#include <cmath>

#include "subsystems/Drivetrain.h"
#include "Config.h"
#include "Constants.h"
#include "nerds/Preferences.h"


DriveByDistance::DriveByDistance(double distance, Drivetrain* drivetrain)
  : drivetrain_(drivetrain),
    PID_(0, 0, 0),
    distance_(distance) {
  AddRequirements({drivetrain_});

  p_ = new double(0);
  i_ = new double(0);
  d_ = new double(0);

  autonomous_drive_tolerance_ = new double(0);
  autonomous_drive_acceleration_ = new double(0);
  autonomous_drive_max_speed_ = new double(0);
  autonomous_drive_min_speed_ = new double(0);
  autonomous_turn_tolerance_ = new double(0);
  autonomous_turn_max_speed_ = new double(0);
  autonomous_turn_min_speed_ = new double(0);

  SetupListeners();
  PID_.EnableContinuousInput(-180, 180);
}

// Called when the command is initially scheduled.
void DriveByDistance::Initialize() {
  initial_heading_ = drivetrain_->GetHeading();
  final_distance_ = drivetrain_->AverageDistance() + distance_;
  initial_distance_ = drivetrain_->AverageDistance();

  PID_.SetPID(*p_, *i_, *d_);
  PID_.SetSetpoint(initial_heading_);
}

// Called repeatedly when this Command is scheduled to run
void DriveByDistance::Execute() {
  double current_heading = drivetrain_->GetHeading();

  double turn = CalculateTurn(
    initial_heading_,
    current_heading,
    *autonomous_turn_tolerance_);

  double current_distance = drivetrain_->AverageDistance();

  double slope = *autonomous_drive_max_speed_ / *autonomous_drive_acceleration_;

  double initial_error = std::fabs(current_distance - initial_distance_);
  double initial_accel = initial_error * slope + *autonomous_drive_min_speed_;

  double final_error = std::fabs(final_distance_ - current_distance);
  double final_accel = final_error * slope + *autonomous_drive_min_speed_;

  double max = std::fabs(*autonomous_drive_max_speed_);

  double speed;

  if (current_distance > final_distance_ + *autonomous_drive_tolerance_) {
    speed = -1;
  } else if (current_distance < final_distance_ - *autonomous_drive_tolerance_) {
    speed = 1;
  } else {
    speed = 0;
  }

  speed = std::min({initial_accel, final_accel, max}) * speed;

  turn = PID_.Calculate(current_heading);

  drivetrain_->ArcadeDrive(speed, turn, false);
}

// Called once the command ends or is interrupted.
void DriveByDistance::End(bool interrupted) {
  drivetrain_->ArcadeDrive(0, 0, false);
  PID_.Reset();
}

// Returns true when the command should end.
bool DriveByDistance::IsFinished() {
  double error = std::fabs(drivetrain_->AverageDistance() - final_distance_);
  if (error < *autonomous_drive_tolerance_) {
    return true;
  }
  return false;
}

double DriveByDistance::CalculateTurn(double target_heading,
    double current_heading, double tolerance) {
  double offset = current_heading - target_heading;

  if (std::fabs(offset) < tolerance) {
    return 0;
  }

  if (offset > 180) {
    return 0.4;
  } else if (offset < -180) {
    return -0.4;
  } else if (offset < 0) {
    return 0.4;
  } else if (offset > 0) {
    return -0.4;
  } else {
    return 0;
  }
}

void DriveByDistance::SetupListeners() {
  // PID
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_P.key, p_);
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_I.key, i_);
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_P.key, p_);

  // Parameters
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_DRIVE_TOLERANCE.key,
    autonomous_drive_tolerance_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_DRIVE_ACCELERATION.key,
    autonomous_drive_acceleration_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_DRIVE_MAX_SPEED.key,
    autonomous_drive_max_speed_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_DRIVE_MIN_SPEED.key,
    autonomous_drive_min_speed_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_TOLERANCE.key,
    autonomous_turn_tolerance_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_MAX_SPEED.key,
    autonomous_turn_max_speed_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_MIN_SPEED.key,
    autonomous_turn_min_speed_);
}
