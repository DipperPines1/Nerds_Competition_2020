/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Launcher.h"

#include <rev/CANPIDController.h>
#include <rev/ControlType.h>

#include "Config.h"
#include "Constants.h"
#include "nerds/Preferences.h"

Launcher::Launcher() :
 master_(CAN_LAUNCHER_MASTER, rev::CANSparkMax::MotorType::kBrushless),
 slave_(CAN_LAUNCHER_SLAVE, rev::CANSparkMax::MotorType::kBrushless)
{
    slave_.Follow(master_, false);

    SetupListeners();
}

// This method will be called once per scheduler run
void Launcher::Periodic() {}
 
void Launcher::SetLauncherSpeed(double speed) {
    rev::CANPIDController controller = master_.GetPIDController();

    controller.SetReference(speed, rev::ControlType::kSmartVelocity);
}

void Launcher::SetupListeners() {
    nerd::Preferences::GetInstance().AddFunctionListener(
            LAUNCHER_CONTROLLER_P.key,
            [this] (
                auto table,
                auto name,
                auto entry,
                auto new_value,
                int flag) -> void {
                    double value = new_value->GetDouble();
                    this->master_.GetPIDController().SetP(value);
                }
    );

     nerd::Preferences::GetInstance().AddFunctionListener(
            LAUNCHER_CONTROLLER_I.key,
            [this] (
                auto table,
                auto name,
                auto entry,
                auto new_value,
                int flag) -> void {
                    double value = new_value->GetDouble();
                    this->master_.GetPIDController().SetI(value);
                }
    );

     nerd::Preferences::GetInstance().AddFunctionListener(
            LAUNCHER_CONTROLLER_D.key,
            [this] (
                auto table,
                auto name,
                auto entry,
                auto new_value,
                int flag) -> void {
                    double value = new_value->GetDouble();
                    this->master_.GetPIDController().SetD(value);
                }
    );

     nerd::Preferences::GetInstance().AddFunctionListener(
            LAUNCHER_MAX_SPEED.key,
            [this] (
                auto table,
                auto name,
                auto entry,
                auto new_value,
                int flag) -> void {
                    double value = new_value->GetDouble();
                    this->master_.GetPIDController().SetSmartMotionMaxVelocity(value);
                }
    );

    nerd::Preferences::GetInstance().AddFunctionListener(
            LAUNCHER_MIN_SPEED.key,
            [this] (
                auto table,
                auto name,
                auto entry,
                auto new_value,
                int flag) -> void {
                    double value = new_value->GetDouble();
                    this->master_.GetPIDController().SetSmartMotionMinOutputVelocity(value);
                }
    );
}
