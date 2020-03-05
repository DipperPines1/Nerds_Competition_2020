/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/WaitCommand.h>

#include "Config.h"
#include "Constants.h"
#include "commands/AutoShoot.h"
#include "commands/RunIntake.h"
#include "commands/SetConveyor.h"
#include "commands/SetLauncher.h"
#include "commands/SetReelSpeed.h"
#include "commands/SpeedSwitch.h"
#include "commands/AlignWithTarget.h"
#include "commands/ToggleExtender.h"
#include "commands/ToggleStopper.h"
#include "nerds/Preferences.h"


RobotContainer::RobotContainer()
  : climber_(),
    drivetrain_(),
    launcher_(),
    oi_(),
    apply_config_(),
    drive_joy_(&drivetrain_, &oi_),
    variable_(&conveyor_, &oi_),
    feed_ball_(false, &conveyor_),
    ball_feed_([this] () -> bool {return this->conveyor_.IsBallDetected();}) {
  ConfigureButtonBindings();

  // Set default commands
  drivetrain_.SetDefaultCommand(drive_joy_);
  conveyor_.SetDefaultCommand(variable_);

  // ball_feed_.WhileActiveOnce(feed_ball_, true);
  auto_chooser_.SetDefaultOption("Shooter Auto", 1);
  auto_chooser_.AddOption("Simple Auto", 2);
  frc::SmartDashboard::PutData("Autonomous/Autonomous Mode", &auto_chooser_);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Commands/Load Config", &apply_config_);

  oi_.BindCommandButton(BUTTON_A, new SetLauncher(&launcher_));
  oi_.BindCommandButton(BUTTON_B, new AlignWithTarget(&drivetrain_));
  oi_.BindCommandButton(BUTTON_LB, new RunIntake(false, &intake_));
  oi_.BindCommandButton(BUTTON_RB, new RunIntake(true, &intake_));
  oi_.BindCommandButton(BUTTON_START, new SpeedSwitch());

  oi_.BindCommandTrigger(DPAD_UP, new ToggleExtender(&climber_));
  oi_.BindCommandTrigger(DPAD_LEFT, new SetReelSpeed(false, &climber_));
  oi_.BindCommandTrigger(DPAD_DOWN, new SetReelSpeed(true, &climber_));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  double follow_line = nerd::Preferences::GetInstance().GetPreference(
    FOLLOW_LINE.key,
    FOLLOW_LINE.value);
  double line_to_ball = nerd::Preferences::GetInstance().GetPreference(
    LINE_TO_BALL.key,
    LINE_TO_BALL.value);
  double grab_ball = nerd::Preferences::GetInstance().GetPreference(
    GRAB_BALLS.key,
    GRAB_BALLS.value);
    double timeout = nerd::Preferences::GetInstance().GetPreference(
      SHOOTER_TIMEOUT.key,
      SHOOTER_TIMEOUT.value);

  int choice = auto_chooser_.GetSelected();

  frc2::Command* command;
  if (choice == 1) {
    command = new frc2::SequentialCommandGroup(
    AutoShoot(&conveyor_, &launcher_).WithTimeout(units::second_t(timeout)),
    TurnByDegree(90, &drivetrain_),
    DriveByDistance(follow_line, &drivetrain_),
    TurnByDegree(90, &drivetrain_),
    DriveByDistance(line_to_ball, &drivetrain_),
    frc2::ParallelRaceGroup(
      RunIntake(false, &intake_),
      DriveByDistance(grab_ball, &drivetrain_)));
  } else if (choice == 2) {
    command = new frc2::SequentialCommandGroup(
      AutoShoot(&conveyor_, &launcher_).WithTimeout(units::second_t(timeout)),
      DriveByDistance(-20, &drivetrain_));
  } else {
    command = new frc2::WaitCommand(2_s);
  }
  return command;
}
