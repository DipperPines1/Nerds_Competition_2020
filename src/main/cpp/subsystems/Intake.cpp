/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"

#include "Config.h"
#include "Constants.h"


Intake::Intake() :
  intake_(CAN_LAUNCHER_INTAKE)
{}

// This method will be called once per scheduler run
void Intake::Periodic() {}

void Intake::RunIntake(double speed) {
  intake_.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}
