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
#include "Constants.h"


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

  std::cout << initial_heading_ << " " << current_Heading << std::endl;

  if (current_Heading == initial_heading_) {
    turn = 0;
  } else if (current_Heading <= initial_heading_ + 180 ||
    current_Heading > initial_heading_) {
    turn = -.4;
  } else if (current_Heading > initial_heading_ - 180 ||
    current_Heading < initial_heading_) {
    turn = .4;
  }

  double yaw_1 = initial_heading_ - current_Heading;
  double yaw_2 = std::fabs(current_Heading + 180) + std::fabs(180 - initial_heading_);

  if(yaw_1 < yaw_2){
    turn = .4;
  } else if (yaw_2 < yaw_1){
    turn = -.4;
  } else {
    turn = 0;
  }

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
