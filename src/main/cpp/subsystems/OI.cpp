/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/OI.h"

#include "Constants.h"


OI::OI() : 
    driver(JOY_DRIVER),
    driver_A(driver, BUTTON_A)
{}

// This method will be called once per scheduler run
void OI::Periodic() {}

