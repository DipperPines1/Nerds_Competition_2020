/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

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
  Drivetrain* drivetrain_;

  double distance_;

  double initial_heading_;
  double final_distance_;
  double initial_distance_;
  double max_speed_;
};
