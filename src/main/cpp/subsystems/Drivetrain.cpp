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
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/smartdashboard/SmartDashboard.h>

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
    odometry({units::degree_t(gyro.GetYaw())})
{
    encoder_left.SetDistancePerPulse(K_ENCODER_DISTANCE_PER_PULSE);
    encoder_right.SetDistancePerPulse(K_ENCODER_DISTANCE_PER_PULSE);

    encoder_left.SetReverseDirection(true);
    encoder_right.SetReverseDirection(false);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    /*double heading = 360 - gyro.GetAngle();
    heading = std::remainder(heading, 360);

    if (heading < 0) {
        heading = 360 + heading;
    }*/

    double heading = -gyro.GetAngle();

    frc::Rotation2d heading_update{units::degree_t(heading)};

    frc::SmartDashboard::PutNumber("Odometry/Heading", heading);

    odometry.Update(
        heading_update,
        units::meter_t(GetDistanceLeft() / 39.3701),
        units::meter_t(GetDistanceRight() / 39.3701));

    auto robot_pose = odometry.GetPose();

    auto robot_translation = robot_pose.Translation();
    auto robot_rotation = robot_pose.Rotation();

    double robot_x = robot_translation.X().to<double>();
    double robot_y = robot_translation.Y().to<double>();
    double robot_degrees = robot_rotation.Degrees().to<double>();

    frc::SmartDashboard::PutNumber("Odometry/Rotation", robot_degrees);
    frc::SmartDashboard::PutNumber("Odometry/X Position", robot_x);
    frc::SmartDashboard::PutNumber("Odometry/Y Position", robot_y);
}

void Drivetrain::ArcadeDrive(double speed, double turn, bool squared) {
    drive_.ArcadeDrive(speed, turn, squared);
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
    double left_rate = encoder_left.GetRate();
    double right_rate = encoder_right.GetRate();

    return {units::meters_per_second_t(left_rate / 39.3701),
        units::meters_per_second_t(right_rate / 39.3701)};
}

double Drivetrain::GetHeading() {
  return gyro.GetYaw();

}

frc::Pose2d Drivetrain::GetPose() {
    return odometry.GetPose();
}

void Drivetrain::TankDrive(double left, double right) {
    drive_.TankDrive(left, right, false);
}
