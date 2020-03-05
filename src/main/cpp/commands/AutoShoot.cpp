/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoShoot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Config.h"
#include "commands/SetConveyor.h"
#include "commands/SetLauncher.h"
#include "nerds/Preferences.h"
#include "subsystems/Conveyor.h"
#include "subsystems/Launcher.h"

AutoShoot::AutoShoot(Conveyor* conveyor, Launcher* shooter) :
conveyor_(conveyor),
shooter_(shooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({conveyor_, shooter_});
}

// Called when the command is initially scheduled.
void AutoShoot::Initialize() {
  double shooter_speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CURRENT_SPEED.key,
    LAUNCHER_CURRENT_SPEED.value);
  shooter_->SetLauncherSpeed(-shooter_speed);
}

// Called repeatedly when this Command is scheduled to run
void AutoShoot::Execute() {
  bool up_to_speed = frc::SmartDashboard::GetBoolean(
    LAUNCHER_UP_TO_SPEED.key,
    LAUNCHER_UP_TO_SPEED.value);
  double conveyor_speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONVEYOR_SPEED.key,
    LAUNCHER_CONVEYOR_SPEED.value);

  if (up_to_speed) {
    conveyor_->RunConveyor(-conveyor_speed);
  } else {
    conveyor_->RunConveyor(0);
  }
}

// Called once the command ends or is interrupted.
void AutoShoot::End(bool interrupted) {
  conveyor_->RunConveyor(0);
  shooter_->SetLauncherSpeed(0);
}

// Returns true when the command should end.
bool AutoShoot::IsFinished() { return false; }
