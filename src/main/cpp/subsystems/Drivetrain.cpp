/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"

#include "Constants.h"


Drivetrain::Drivetrain() :
    front_left(CAN_DRIVE_FRONT_LEFT),
    front_right(CAN_DRIVE_FRONT_RIGHT),
    back_left(CAN_DRIVE_BACK_LEFT),
    back_right(CAN_DRIVE_BACK_RIGHT),
    left(front_left, back_left),
    right(front_right, back_right),
    drive(left, right)
{}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {}

void Drivetrain::ArcadeDrive(double speed, double turn, bool squared) {
    drive.ArcadeDrive(speed, turn, squared);
}