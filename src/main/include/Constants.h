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

// Axis ID
constexpr int AXIS_LEFT_X = 0;
constexpr int AXIS_RIGHT_X = 4;
constexpr int AXIS_LEFT_Y = 1;
constexpr int AXIS_RIGHT_Y = 5;
constexpr int BUMPER_LEFT = 2;
constexpr int BUMPER_RIGHT = 3;

// Serial Ports
constexpr int SERIAL_GYRO = 0;

// Digital IOs
constexpr int DIO_ENCODER_LEFT_A = 0;
constexpr int DIO_ENCODER_LEFT_B = 1;
constexpr int DIO_ENCODER_RIGHT_A = 2;
constexpr int DIO_ENCODER_RIGHT_B = 3;

// Feedforward/Feedback Gains
// Units are in inches
constexpr double KS = 0.688;
constexpr double KA = 0.00502;
constexpr double KV = 0.0811;
constexpr double KP_DRIVE_VELOCITY = 0.213;
constexpr double K_TRACK_WIDTH = 25.12;
extern const frc::DifferentialDriveKinematics K_DRIVE_KINEMATICS;
constexpr double K_MAX_SPEED = 1;
constexpr double K_MAX_ACCELERATION = 1;
constexpr double K_RAMSETE_B = 78.7402;
constexpr double K_RAMSETE_ZETA = 27.5591;
constexpr double K_ENCODER_DISTANCE_PER_PULSE = 3.14159 / 60;
constexpr bool K_GYRO_REVERSED = false;
