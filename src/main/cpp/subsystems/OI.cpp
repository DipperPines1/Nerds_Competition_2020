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
    driver_A_(&driver_, BUTTON_A),
    driver_B_(&driver_, BUTTON_B),
    driver_X_(&driver_, BUTTON_X),
    driver_Y_(&driver_, BUTTON_Y),
    driver_LB_(&driver_, BUTTON_LB),
    driver_RB_(&driver_, BUTTON_RB),
    trigger_left_([this] () -> bool {
        double trigger_value = this->GetAxis(TRIGGER_LEFT);
        return trigger_value > 0.2;
    }),
    trigger_right_([this] () -> bool {
        double trigger_value = this->GetAxis(TRIGGER_RIGHT);
        return trigger_value > 0.2;
    } )
{}

// This method will be called once per scheduler run
void OI::Periodic() {}

double OI::GetAxis(int axis) {
    return driver_.GetRawAxis(axis);
}

void OI::BindCommandButton(int button, frc2::Command* command) {
    switch (button) {
    case BUTTON_A:
        bound_commands_.push_back(command);
        driver_A_.WhenPressed(command, true);
        return;
    case BUTTON_B:
        bound_commands_.push_back(command);
        driver_B_.WhenPressed(command, true);
        return;
    case BUTTON_X:
        bound_commands_.push_back(command);
        driver_X_.WhenPressed(command, true);
        return;
    case BUTTON_Y:
        bound_commands_.push_back(command);
        driver_Y_.WhenPressed(command, true);
        return;
    case BUTTON_LB:
        bound_commands_.push_back(command);
        driver_LB_.WhileHeld(command, true);
        return;
    default:
        std::stringstream warning;
        warning << "Button: " << button << " does not exist.";
        frc::DriverStation::ReportWarning(warning.str());
    }
}

void OI::BindCommandTrigger(int trigger, frc2::Command* command) {
    switch (trigger) {
    case TRIGGER_LEFT:
        bound_commands_.push_back(command);
        trigger_left_.WhileActiveContinous(command, true);
        return;
    case TRIGGER_RIGHT:
        bound_commands_.push_back(command);
        trigger_right_.WhileActiveContinous(command, true);
    return;
    default:
        std::stringstream warning;
        warning << "Trigger: " << trigger << " does not exist.";
        frc::DriverStation::ReportWarning(warning.str());
    }
}