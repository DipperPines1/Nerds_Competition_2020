/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/controller/PIDController.h>
#include <frc2/Timer.h>

class Drivetrain;

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TurnByDegree
    : public frc2::CommandHelper<frc2::CommandBase, TurnByDegree> {
 public:
  TurnByDegree(double degree, Drivetrain*);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  void SetupListeners();

  Drivetrain* drivetrain_;

  frc2::PIDController PID_;

  // PID variables
  double* p_;
  double* i_;
  double* d_;
  double* time_on_target_;

  // Parameter Listener Variables
  double* autonomous_turn_tolerance_;
  double* autonomous_turn_max_speed_;
  double* autonomous_turn_min_speed_;

  double degrees_;

  frc2::Timer timer_;
  bool running_;
};
