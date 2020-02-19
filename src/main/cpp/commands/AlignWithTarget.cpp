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
#include "frc/Timer.h"

AlignWithTarget::AlignWithTarget(Drivetrain* drivetrain)
  : drivetrain_(drivetrain),
  vision_PID_(0, 0, 0),
  timer_() {
  // Use AddRequirements() here to declare subsystem dependencies.
  AddRequirements({drivetrain_});

  tolerence_ = new double(0);
  turn_ = new double(0);
  vision_PID_.SetSetpoint(0);
}

// Called when the command is initially scheduled.
void AlignWithTarget::Initialize() {
  vision_PID_.SetPID(*p_, *i_, *d_);
  vision_PID_.SetTolerance(*tolerence_);
}

// Called repeatedly when this Command is scheduled to run
void AlignWithTarget::Execute() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);

  double turn = vision_PID_.Calculate(Center_X);

  drivetrain_->ArcadeDrive(0, -turn, false);
}

// Called once the command ends or is interrupted.
void AlignWithTarget::End(bool interrupted) {
    drivetrain_->ArcadeDrive(0, 0, false);
    vision_PID_.Reset()
}

// Returns true when the command should end.
bool AlignWithTarget::IsFinished() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);
  if (vision_PID_.AtSetpoint()) {
    timer_.Start();
  }else{
    timer_.Reset();
  }

  return -*tolerence_ < Center_X && Center_X < *tolerence_;
}

void AlignWithTarget::SetupListeners() {
  p_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_PID_P.key,
  p_);
  i_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_PID_I.key,
  i_);
  d_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_PID_D.key,
  d_);
  timeontarget_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  PID_TIME_ON_TARGET.key,
  timeontarget_);
  turn_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_TURN_SPEED.key,
  turn_);
  tolerence_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_TOLERANCE.key,
  tolerence_);
}
