/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/controller/PIDController.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Drivetrain.h"

class Drivetrain;

class DriveByDistance
    : public frc2::CommandHelper<frc2::CommandBase, DriveByDistance> {
 public:
  DriveByDistance(double distance, Drivetrain*);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  /**
   * @brief returns the rate at which the robot must turn to reach the target heading from the current heading
   * 
   * @param target_heading The target heading the robot should be turning towards
   * @param current_heading The robot's current heading
   * @param tolerance The tolerance range of the heading.
   * @return double The rate at which the robot should turn to achieve the target heading
   */
  double CalculateTurn(
    double target_heading,
    double current_heading,
    double tolerance);

  /**
   * @brief Sets up the listeners for the PID controller
   * 
   */
  void SetupListeners();

  Drivetrain* drivetrain_;

  frc2::PIDController PID_;

  double* p_;
  double* i_;
  double* d_;

  double distance_;
  double initial_heading_;
  double final_distance_;
  double initial_distance_;
  double max_speed_;
};
