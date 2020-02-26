/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Sensors.h"

#include "subsystems/Conveyor.h"
#include "Config.h"
#include "nerds/Preferences.h"

Sensors::Sensors(Conveyor* conveyor) :
  conveyor_(conveyor),
  sensor_input_(0),
  sensor_output_(0) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({conveyor_});
}

// Called when the command is initially scheduled.
void Sensors::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Sensors::Execute() {
  double speed = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONVEYOR_SPEED.key,
    LAUNCHER_CONVEYOR_SPEED.value);

  bool detected = sensor_input_.Get();

  if (detected) {
    conveyor_->RunConveyor(speed);
  }
}

// Called once the command ends or is interrupted.
void Sensors::End(bool interrupted) {}

// Returns true when the command should end.
bool Sensors::IsFinished() { return true; }
