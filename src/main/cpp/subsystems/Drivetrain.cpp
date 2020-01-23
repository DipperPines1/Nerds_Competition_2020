/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"

#include <frc/SerialPort.h>
#include <frc/geometry/Pose2D.h>
#include <frc/geometry/Rotation2D.h>


#include "Constants.h"

Drivetrain::Drivetrain() :
    front_left_(CAN_DRIVE_FRONT_LEFT),
    front_right_(CAN_DRIVE_FRONT_RIGHT),
    back_left_(CAN_DRIVE_BACK_LEFT),
    back_right_(CAN_DRIVE_BACK_RIGHT),
    left_(front_left_, back_left_),
    right_(front_right_, back_right_),
    drive_(left_, right_),
    gyro(frc::SerialPort::Port::kUSB1),
    encoder_left(DIO_ENCODER_LEFT_A, DIO_ENCODER_LEFT_B, false),
    encoder_right(DIO_ENCODER_RIGHT_A, DIO_ENCODER_RIGHT_B, true),
    odometry({}, {})
{
    encoder_left.SetDistancePerPulse(K_ENCODER_DISTANCE_PER_PULSE);
    encoder_right.SetDistancePerPulse(K_ENCODER_DISTANCE_PER_PULSE);

    encoder_left.SetReverseDirection(true);
    encoder_right.SetReverseDirection(true);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    odometry.Update(
        frc::Rotation2d(units::degree_t(GetHeading())),
        units::inch_t(GetDistanceLeft()),
        units::inch_t(GetDistanceRight()));
}

void Drivetrain::ArcadeDrive(double speed, double turn, bool squared) {
    drive_.ArcadeDrive(speed, turn, squared);
}

double Drivetrain::GetHeading() {
    return gyro.GetCompassHeading();
}

double Drivetrain::GetDistanceLeft() {
    return encoder_left.GetDistance();
}

double Drivetrain::GetDistanceRight() {
    return encoder_right.GetDistance();
}

double Drivetrain::AverageDistance() {
    return (encoder_left.GetDistance() + encoder_right.GetDistance()) / 2.0;
}

frc::DifferentialDriveWheelSpeeds Drivetrain::WheelSpeed() {
    return {units::meters_per_second_t(encoder_left.GetRate()),
        units::meters_per_second_t(encoder_right.GetRate())};
}

double Drivetrain::GetHeading() {
  return std::remainder(gyro.GetAngle(), 360) * (K_GYRO_REVERSED ? -1.0 : 1.0);
}

frc::Pose2d Drivetrain::GetPose() {
    return odometry.GetPose();
}

void Drivetrain::TankDriveVolts(units::volt_t left, units::volt_t right) {
  left_.SetVoltage(left);
  right_.SetVoltage(-right);
}
