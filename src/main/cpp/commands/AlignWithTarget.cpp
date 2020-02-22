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
  SetupListeners();
  vision_PID_.SetSetpoint(0);
}

// Called when the command is initially scheduled.
void AlignWithTarget::Initialize() {
  vision_PID_.SetPID(*p_, *i_, *d_);
  vision_PID_.SetTolerance(*tolerence_);

  running_ = false;
  timer_.Reset();
}

// Called repeatedly when this Command is scheduled to run
void AlignWithTarget::Execute() {
  double Center_X = frc::SmartDashboard::GetNumber(
    VISION_CENTER_X.key,
    VISION_CENTER_X.value);

  double output = vision_PID_.Calculate(Center_X);

  double turn;
  if (vision_PID_.AtSetpoint()) {
    turn = 0;
  } else {
    double slope = *turn_max_ - *turn_min_;
    turn = slope * std::fabs(output) + *turn_min_;

    if (turn > *turn_max_) {
      turn = *turn_max_;
    }

    turn *= output > 0 ? 1 : -1;
  }

  drivetrain_->ArcadeDrive(0, -turn, false);
}

// Called once the command ends or is interrupted.
void AlignWithTarget::End(bool interrupted) {
    drivetrain_->ArcadeDrive(0, 0, false);
    vision_PID_.Reset();
}

// Returns true when the command should end.
bool AlignWithTarget::IsFinished() {
  if (vision_PID_.AtSetpoint()) {
    if (!running_) {
      timer_.Start();
      running_ = true;
    } else {
      return timer_.Get().to<double>() > *timeontarget_;
    }
  } else if (running_) {
    timer_.Reset();
    running_ = false;
  }

  return false;
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
  turn_max_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_TURN_MAX_SPEED.key,
  turn_max_);
  turn_min_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_TURN_MIN_SPEED.key,
  turn_min_);
  tolerence_ = new double(0);
  nerd::Preferences::GetInstance().AddListener(
  VISION_TOLERANCE.key,
  tolerence_);
}
