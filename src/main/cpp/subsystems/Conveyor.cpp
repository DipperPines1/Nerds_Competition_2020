/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Conveyor.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Config.h"
#include "Constants.h"
#include "nerds/Preferences.h"

Conveyor::Conveyor() :
conveyor_(PWM_LAUNCHER_CONVEYOR),
ball_sensor_(DIO_BALL_SENSOR) {
  feed_override_ = new bool(false);
  nerd::Preferences::GetInstance().AddListener(
    CONVEYOR_FEED_OVERRIDE.key,
    feed_override_);
}

// This method will be called once per scheduler run
void Conveyor::Periodic() {
  frc::SmartDashboard::PutBoolean(
    "Conveyor/Ball is Detected",
    IsBallDetected());
}

void Conveyor::RunConveyor(double speed) {
  conveyor_.Set(speed);
}

bool Conveyor::IsBallDetected() {
  return !ball_sensor_.Get() && !*feed_override_;
}
