/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignWithTarget.h"

#include <frc/SmartDashboard/SmartDashboard.h>
#include "Config.h"
#include "subsystems/Drivetrain.h"
#include "nerds/Preferences.h"

AlignWithTarget::AlignWithTarget(Drivetrain* drivetrain)
  : drivetrain_(drivetrain) {
  // Use AddRequirements() here to declare subsystem dependencies.
  AddRequirements({drivetrain_});

  tolerence_ = new double(0);
  turn_ = new double(0);

    nerd::Preferences::GetInstance().AddListener(
    VISION_TURN_SPEED.key,
    turn_);

    nerd::Preferences::GetInstance().AddListener(
    VISION_TOLERANCE.key,
    tolerence_);
}

// Called when the command is initially scheduled.
void AlignWithTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AlignWithTarget::Execute() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);

  bool reverse = Center_X < 0;

  if (-*tolerence_ < Center_X && Center_X < *tolerence_) {
    drivetrain_->ArcadeDrive(0, 0, false);
  }

  drivetrain_->ArcadeDrive(0, *turn_ * (reverse ? -1.0 : 1.0), false);
}

// Called once the command ends or is interrupted.
void AlignWithTarget::End(bool interrupted) {
    drivetrain_->ArcadeDrive(0, 0, false);
}

// Returns true when the command should end.
bool AlignWithTarget::IsFinished() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);

  return -*tolerence_ < Center_X && Center_X < *tolerence_;
}
