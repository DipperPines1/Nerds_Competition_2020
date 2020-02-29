/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Constants.h"
#include "commands/RunIntake.h"
#include "commands/SetConveyor.h"
#include "commands/SetLauncher.h"
#include "commands/SetReelSpeed.h"
#include "commands/SpeedSwitch.h"
#include "commands/ToggleExtender.h"
#include "commands/ToggleStopper.h"


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
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Commands/Load Config", &apply_config_);

  oi_.BindCommandButton(BUTTON_A, new SetLauncher(&launcher_));
  oi_.BindCommandButton(BUTTON_B, new ToggleStopper(&climber_));
  oi_.BindCommandButton(BUTTON_LB, new RunIntake(false, &intake_));
  oi_.BindCommandButton(BUTTON_RB, new RunIntake(true, &intake_));
  oi_.BindCommandButton(BUTTON_START, new SpeedSwitch());

  oi_.BindCommandTrigger(DPAD_UP, new ToggleExtender(&climber_));
  oi_.BindCommandTrigger(DPAD_LEFT, new SetReelSpeed(false, &climber_));
  oi_.BindCommandTrigger(DPAD_DOWN, new SetReelSpeed(true, &climber_));
  // oi_.BindCommandTrigger(TRIGGER_LEFT, new SetConveyor(false, &conveyor_));
  // oi_.BindCommandTrigger(TRIGGER_RIGHT, new SetConveyor(true, &conveyor_));
}
frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
