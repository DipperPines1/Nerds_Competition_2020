/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ConveyorVariable.h"

#include "Config.h"
#include "Constants.h"

#include "nerds/Preferences.h"

#include "subsystems/Conveyor.h"
#include "subsystems/OI.h"

ConveyorVariable::ConveyorVariable(Conveyor* conveyor, OI* oi) :
  oi_(oi),
  conveyor_(conveyor) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({conveyor_});
}

// Called when the command is initially scheduled.
void ConveyorVariable::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ConveyorVariable::Execute() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONVEYOR_SPEED.key,
    LAUNCHER_CONVEYOR_SPEED.value);

  double left = oi_->GetAxis(TRIGGER_LEFT);
  double right = oi_->GetAxis(TRIGGER_RIGHT);

  double input = right - left;

  double output = speed * input;

  conveyor_->RunConveyor(output);
}

// Called once the command ends or is interrupted.
void ConveyorVariable::End(bool interrupted) {
  conveyor_->RunConveyor(0);
}

// Returns true when the command should end.
bool ConveyorVariable::IsFinished() { return false; }
