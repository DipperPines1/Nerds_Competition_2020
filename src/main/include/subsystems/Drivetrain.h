/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <AHRS.h>
#include <frc/Encoder.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <units/units.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/trajectory/TrajectoryConfig.h>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /**
   * @brief Move the robot using an arcade drive control scheme.
   * 
   * @param speed The forward/backwards speed.
   * 
   * @param turn The rate at which the robot turns.
   * 
   * @param squared If true, inputs are squared.
   */
  void ArcadeDrive(double speed, double turn, bool squared);

  /**
   * @brief Get the heading of the gyro on the drivetrain
   * 
   * @return double The robot's current heading
   */
  double GetHeading();

  /**
   * @brief get the distance the robot has travelled on the left side
   * 
   * @return double how far the robot has gone on the left side
   */
  double GetDistanceLeft();

  /**
   * @brief get the distance the robot has travelled on the right side
   * 
   * @return double how far the robot has gone on the right side
   */
  double GetDistanceRight();

  /**
   * @brief takes the average of the distance the robot has travelled on the left and right sides
   * 
   * @return double how far the robot has gone
   */
  double AverageDistance();

  /**
   * @brief Gets the speed of the wheels
   * 
   * @return frc::DifferentialDriveWheelSpeeds 
   */
  frc::DifferentialDriveWheelSpeeds WheelSpeed();

  /**
   * @brief Gets the Pose object
   * 
   * @return frc::Pose2d 
   */
  frc::Pose2d GetPose();

  /**
   * @brief Sets the voltage on both motors
   * 
   * @param left The left motors
   * 
   * @param right The right motors
   */
  void TankDriveVolts(units::volt_t left, units::volt_t right);

  /**
   * @brief Gets the Trajectory Config object
   * 
   * @return frc::TrajectoryConfig 
   */
  const frc::TrajectoryConfig& GetTrajectoryConfig();

/**
 * @brief Makes the Trajectory reversed or not
 * 
 * @param reversed 
 */
  void SetTrajectoryReversed(bool reversed);

/**
 * @brief Get the Drive Kinematics object
 * 
 * @return const frc::DifferentialDriveKinematics& 
 */
  const frc::DifferentialDriveKinematics& GetDriveKinematics();

 private:
  void SetupListeners();

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX front_left_;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX front_right_;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX back_left_;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX back_right_;

  frc::SpeedControllerGroup left_;
  frc::SpeedControllerGroup right_;

  frc::DifferentialDrive drive_;

  AHRS gyro;

  frc::Encoder encoder_left;
  frc::Encoder encoder_right;

  frc::DifferentialDriveOdometry odometry;

  frc::DifferentialDriveKinematics drive_kinematics;
  frc::SimpleMotorFeedforward<units::meters> simple_motor_feedforward;
  frc::DifferentialDriveVoltageConstraint voltage_constraint;
  frc::TrajectoryConfig trajectory_config;
};