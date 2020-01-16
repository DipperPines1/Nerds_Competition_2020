/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveByDistance.h"

#include "subsystems/Drivetrain.h"

DriveByDistance::DriveByDistance(double distance, Drivetrain* drivetrain)
  : drivetrain_(drivetrain),
    distance_(distance) {
  AddRequirements({drivetrain_});
}

// Called when the command is initially scheduled.
void DriveByDistance::Initialize() {
  double initial_heading_ = drivetrain_->GetHeading();
  double final_distance_ = drivetrain_->AverageDistance() + distance_;
}

// Called repeatedly when this Command is scheduled to run
void DriveByDistance::Execute() {
  double current_Heading = drivetrain_->GetHeading();
  if (current_Heading == initial_heading_) {
    drivetrain_->ArcadeDrive(.8, 0, false);
  } else if (current_Heading <= initial_heading_ + 180 ||
    current_Heading > initial_heading_) {
    drivetrain_->ArcadeDrive(.4, -.8, false);
  } else if (current_Heading > initial_heading_ - 180 ||
    current_Heading < initial_heading_) {
    drivetrain_->ArcadeDrive(.4, .8, false);
  } else {
    drivetrain_->ArcadeDrive(0, 0, false);
  }
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
