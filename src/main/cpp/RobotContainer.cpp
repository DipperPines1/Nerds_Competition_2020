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

#include "Constants.h"
#include "commands/RunIntake.h"
#include "commands/SetLauncher.h"
#include "commands/SetConveyor.h"
#include "commands/SetReelSpeed.h"
#include "commands/SpeedSwitch.h"
#include "commands/ToggleExtender.h"
#include "commands/ToggleStopper.h"


RobotContainer::RobotContainer()
  : drivetrain_(),
    launcher_(),
    climber_(),
    oi_(),
    apply_config_(),
    drive_joy_(&drivetrain_, &oi_) {
  ConfigureButtonBindings();

  // Set default commands
  drivetrain_.SetDefaultCommand(drive_joy_);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Commands/Load Config", &apply_config_);

  oi_.BindCommandButton(BUTTON_A, new SpeedSwitch());
  oi_.BindCommandButton(BUTTON_X, new ToggleExtender(&climber_));
  oi_.BindCommandButton(BUTTON_LB, new RunIntake(false, &launcher_));
  oi_.BindCommandButton(BUTTON_RB, new RunIntake(true, &launcher_));

  oi_.BindCommandTrigger(TRIGGER_RIGHT, new SetLauncher(&launcher_));
  oi_.BindCommandTrigger(TRIGGER_LEFT, new SetConveyor(false, &launcher_));
  oi_.BindCommandTrigger(DPAD_LEFT, new SetConveyor(true, &launcher_));
  oi_.BindCommandButton(BUTTON_Y, new SetReelSpeed(&climber_));
  oi_.BindCommandButton(BUTTON_B, new ToggleStopper(&climber_));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  frc2::SequentialCommandGroup* command = new frc2::SequentialCommandGroup(
    DriveByDistance(24, &drivetrain_),
    frc2::ParallelRaceGroup{
      SetLauncher(&launcher_),
      SetConveyor(false, &launcher_).WithTimeout(5_s)
    },
    DriveByDistance(-24, &drivetrain_));
  return command;
} 
