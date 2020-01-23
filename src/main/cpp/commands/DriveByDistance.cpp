/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveByDistance.h"

#include <algorith>

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include <cmath>

DriveByDistance::DriveByDistance(double distance, Drivetrain* drivetrain)
  : drivetrain_(drivetrain),
    distance_(distance) {
  AddRequirements({drivetrain_});
}

// Called when the command is initially scheduled.
void DriveByDistance::Initialize() {
  initial_heading_ = drivetrain_->GetHeading();
  final_distance_ = drivetrain_->AverageDistance() + distance_;
  initial_distance_ = drivetrain_->AverageDistance();
}

// Called repeatedly when this Command is scheduled to run
void DriveByDistance::Execute() {

  double speed = 0.3, turn = 0;
  double current_Heading = drivetrain_->GetHeading();
  if (current_Heading == initial_heading_) {
    turn = 0;
  } else if (current_Heading <= initial_heading_ + 180 ||
    current_Heading > initial_heading_) {
    turn = -.4;
  } else if (current_Heading > initial_heading_ - 180 ||
    current_Heading < initial_heading_) {
    turn = .4;
  }

  if (drivetrain_->AverageDistance() > final_distance_ + DISTANCE_ERROR_RANGE) {
    speed *= -1;
  } else if (drivetrain_->AverageDistance() < final_distance_ - DISTANCE_ERROR_RANGE) {
  
  } else {
    speed = 0;
  }

  double initial_accel = std::abs(drivetrain_->AverageDistance() - initial_distance_) * (max_speed_ / distance_);
  double final_accel = std::abs(distance - drivetrain_->AverageDistance()) * (max_speed_ / distance_);
  double max = std::abs(max_speed_);
  speed = std::min({initial_accel, final_accel, max}) * ((speed < 0) ? 1 : -1);


  drivetrain_->ArcadeDrive(speed, turn, false);
}

// Called once the command ends or is interrupted.
void DriveByDistance::End(bool interrupted) {
  drivetrain_->ArcadeDrive(0, 0, false);
}

// Returns true when the command should end.
bool DriveByDistance::IsFinished() {
  if (final_distance_ == drivetrain_->AverageDistance()) {
    return true;
  }
  return false;
}
