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

class Drivetrain;

class DriveByDistance
    : public frc2::CommandHelper<frc2::CommandBase, DriveByDistance> {
 public:
  DriveByDistance(double distance, Drivetrain*);
  DriveByDistance(
    double distance,
    double min_speed,
    double max_speed,
    Drivetrain*);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  /**
   * @brief Sets up the listeners for the PID controller
   * 
   */
  void SetupListeners();

  Drivetrain* drivetrain_;

  frc2::PIDController PID_;

  // PID Listener Variables
  double* p_;
  double* i_;
  double* d_;

  // Parameter Listener Variables
  double* autonomous_drive_tolerance_;
  double* autonomous_drive_acceleration_;
  double* autonomous_drive_max_speed_;
  double* autonomous_drive_min_speed_;
  double* autonomous_turn_tolerance_;
  double* autonomous_turn_max_speed_;
  double* autonomous_turn_min_speed_;


  double distance_;
  double initial_heading_;
  double final_distance_;
  double initial_distance_;
  double max_speed_;
};
