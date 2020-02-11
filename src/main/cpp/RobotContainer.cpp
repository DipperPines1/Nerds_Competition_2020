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
#include "commands/SetLauncher.h"
#include "commands/SetConveyor.h"
#include "commands/SpeedSwitch.h"


RobotContainer::RobotContainer()
  : drivetrain_(),
    launcher_(),
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
  oi_.BindCommandTrigger(TRIGGER_RIGHT, new SetLauncher(&launcher_));
  oi_.BindCommandButton(BUTTON_LB, new RunIntake(&launcher_));
  oi_.BindCommandTrigger(TRIGGER_LEFT, new SetConveyor(&launcher_));
}
frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
