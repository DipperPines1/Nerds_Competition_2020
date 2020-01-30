/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/OI.h"

#include <sstream>

#include <frc/DriverStation.h>

#include "Constants.h"

OI::OI() :
    driver_(JOY_DRIVER),
    driver_A_(&driver_, BUTTON_A)
{}

// This method will be called once per scheduler run
void OI::Periodic() {}

double OI::GetAxis(int axis) {
    return driver_.GetRawAxis(axis);
}

void OI::BindCommandButton(int button, frc2::Command* command) {
    switch(button){
    case BUTTON_A:
        bound_commands_.push_back(command);
        driver_A_.WhenPressed(command, true);
        return;
    default:
        std::stringstream warning;
        warning << "Button: " << button << " does not exist.";
        frc::DriverStation::ReportWarning(warning.str());
    }
}