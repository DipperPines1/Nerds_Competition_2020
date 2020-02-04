/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleExtender.h"

#include "subsystems/Climber.h"

ToggleExtender::ToggleExtender(Climber* climber) :
  climber_(climber)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({climber_});
}

// Called when the command is initially scheduled.
void ToggleExtender::Initialize() {
  bool state = climber_->GetExtender();
  climber_->SetExtender(!state);
}

// Called repeatedly when this Command is scheduled to run
void ToggleExtender::Execute() {}

// Called once the command ends or is interrupted.
void ToggleExtender::End(bool interrupted) {}

// Returns true when the command should end.
bool ToggleExtender::IsFinished() { return true; }
