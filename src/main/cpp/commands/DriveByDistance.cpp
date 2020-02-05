/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveByDistance.h"

#include <algorithm>
#include <cmath>

#include <iostream>

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
  double speed = 0.3, turn = 0;
  double current_heading = drivetrain_->GetHeading();

  turn = CalculateTurn(initial_heading_, current_heading, HEADING_ERROR_RAGE);

  double current_distance = drivetrain_->AverageDistance();

  if (current_distance > final_distance_ + DISTANCE_ERROR_RANGE) {
    speed *= -1;
  } else if (current_distance < final_distance_ - DISTANCE_ERROR_RANGE) {
  
  } else {
    speed = 0;
  }

  double slope = MAX_SPEED / ACCELERATION_DISTANCE;

  double initial_accel = std::fabs(current_distance - initial_distance_) * slope + MIN_SPEED;
  double final_accel = std::fabs(final_distance_ - current_distance) * slope + MIN_SPEED;
  double max = std::fabs(MAX_SPEED);

  speed = std::min({initial_accel, final_accel, max}) * ((speed >= 0) ? 1 : -1);

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
  if (final_distance_ == drivetrain_->AverageDistance()) {
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
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_P.key, p_);
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_I.key, i_);
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_P.key, p_);
}