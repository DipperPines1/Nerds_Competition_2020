/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

// CAN Devices
constexpr int CAN_DRIVE_FRONT_RIGHT = 3;
constexpr int CAN_DRIVE_BACK_RIGHT = 4;
constexpr int CAN_DRIVE_FRONT_LEFT = 5;
constexpr int CAN_DRIVE_BACK_LEFT = 6;

// Controller const
constexpr int JOY_DRIVER = 0;
constexpr int BUTTON_A = 1;

// axis ID
constexpr int AXIS_LEFT_X = 0;
constexpr int AXIS_RIGHT_X = 4;
constexpr int AXIS_LEFT_Y = 1;
constexpr int AXIS_RIGHT_Y = 5;
constexpr int BUMPER_LEFT = 2;
constexpr int BUMPER_RIGHT = 3;

// serial ports
constexpr int SERIAL_GYRO = 0;

// Digital IOs
constexpr int DIO_ENCODER_LEFT_A = 0;
constexpr int DIO_ENCODER_LEFT_B = 1;
constexpr int DIO_ENCODER_RIGHT_A = 2;
constexpr int DIO_ENCODER_RIGHT_B = 3;

// Encoder constants
constexpr double WHEEL_DIAMETER = 5.5;
constexpr double PI = 3.14159;
constexpr double PULSES_PER_REVOLUTION = 360;

// Autonomous constants
constexpr double DISTANCE_ERROR_RANGE = 0.25;
constexpr double ACCELERATION_DISTANCE = 8;
constexpr double MAX_SPEED = 0.6;
constexpr double MIN_SPEED = .25;
constexpr double HEADING_ERROR_RAGE = 2;
