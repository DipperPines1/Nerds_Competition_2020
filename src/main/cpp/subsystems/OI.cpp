/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/OI.h"

#include <frc/DriverStation.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/Timer.h>
#include <sstream>

#include "Constants.h"
#include "Config.h"

OI::OI() :
    driver_(JOY_DRIVER),
    driver_A_(&driver_, BUTTON_A),
    driver_B_(&driver_, BUTTON_B),
    driver_X_(&driver_, BUTTON_X),
    driver_Y_(&driver_, BUTTON_Y),
    driver_LB_(&driver_, BUTTON_LB),
    driver_RB_(&driver_, BUTTON_RB),
    driver_START_(&driver_, BUTTON_START),
    driver_BACK_(&driver_, BUTTON_BACK),
    trigger_left_([this] () -> bool {
        double trigger_value = this->GetAxis(TRIGGER_LEFT);
        return trigger_value > 0.2;
    }),
    trigger_right_([this] () -> bool {
        double trigger_value = this->GetAxis(TRIGGER_RIGHT);
        return trigger_value > 0.2;
    }),
    up_([this] () -> bool {
        int pov = this->GetPOV();
        return pov >= 315 || (pov >= 0 && pov <= DPAD_UP + 45);
    }),
    down_([this] () -> bool {
        int pov = this->GetPOV();
        return pov >= DPAD_DOWN - 45 && pov <= DPAD_DOWN + 45;
    }),
    left_([this] () -> bool {
        int pov = this->GetPOV();
        return pov >= DPAD_LEFT - 45 && pov <= DPAD_LEFT + 45;
    }),
    right_([this] () -> bool {
        int pov = this->GetPOV();
        return pov >= DPAD_RIGHT - 45 && pov <= DPAD_RIGHT + 45;
    }) {
    frc::SmartDashboard::PutBoolean(
        POV_ENABLED.key,
        false);
}

// This method will be called once per scheduler run
void OI::Periodic() {
    auto time = frc2::Timer::GetMatchTime();
    if ( time > 120_s ) {
        frc::SmartDashboard::PutBoolean(
            POV_ENABLED.key,
            true);
    }
}

double OI::GetAxis(int axis) {
    return driver_.GetRawAxis(axis);
}

int OI::GetPOV() {
    bool enabled = frc::SmartDashboard::GetBoolean(
        POV_ENABLED.key,
        false);

    if (!enabled) {
        return -1;
    }

    return driver_.GetPOV();
}

void OI::BindCommandButton(int button, frc2::Command* command) {
    switch (button) {
    case BUTTON_A:
        bound_commands_.push_back(command);
        driver_A_.ToggleWhenPressed(command, true);
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
        driver_Y_.WhenHeld(command, true);
        return;
    case BUTTON_LB:
        bound_commands_.push_back(command);
        driver_LB_.ToggleWhenPressed(command, true);
        return;
    case BUTTON_RB:
        bound_commands_.push_back(command);
        driver_RB_.ToggleWhenPressed(command, true);
        return;
    case BUTTON_START:
        bound_commands_.push_back(command);
        driver_START_.ToggleWhenPressed(command, true);
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
        trigger_left_.WhenHeld(command, true);
        return;
    case TRIGGER_RIGHT:
        bound_commands_.push_back(command);
        trigger_right_.WhenHeld(command, true);
        return;
    case DPAD_LEFT:
        bound_commands_.push_back(command);
        left_.WhenHeld(command, true);
        return;
    case DPAD_RIGHT:
        bound_commands_.push_back(command);
        right_.WhenHeld(command, true);
        return;
    case DPAD_UP:
        bound_commands_.push_back(command);
        up_.ToggleWhenPressed(command, true);
        return;
    case DPAD_DOWN:
        bound_commands_.push_back(command);
        down_.WhenHeld(command, true);
        return;
    default:
        std::stringstream warning;
        warning << "Trigger: " << trigger << " does not exist.";
        frc::DriverStation::ReportWarning(warning.str());
    }
}
