/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

namespace nerd {

template <typename T>
struct ConfigKey {
  std::string key;
  T value;
};

}  // namespace nerd

// Joysticks
const nerd::ConfigKey<double> JOYSTICK_DRIVE_MAX_HIGH{
  "Joysticks/Drive/Max Speed/High",
  1
};
const nerd::ConfigKey<double> JOYSTICK_DRIVE_MAX_LOW{
  "Joysticks/Drive/Max Speed/Low",
  0.6
};
const nerd::ConfigKey<double> JOYSTICK_DRIVE_MIN_HIGH{
  "Joysticks/Drive/Min Speed/High",
  0.35
};
const nerd::ConfigKey<double> JOYSTICK_DRIVE_MIN_LOW{
  "Joysticks/Drive/Min Speed/Low",
  0.35
};
const nerd::ConfigKey<double> JOYSTICK_TURN_MAX_HIGH{
  "Joysticks/Turn/Max Speed/High",
  1
};
const nerd::ConfigKey<double> JOYSTICK_TURN_MAX_LOW{
  "Joysticks/Turn/Max Speed/Low",
  0.6
};
const nerd::ConfigKey<double> JOYSTICK_TURN_MIN_HIGH{
  "Joysticks/Turn/Min Speed/High",
  0.35
};
const nerd::ConfigKey<double> JOYSTICK_TURN_MIN_LOW{
  "Joysticks/Turn/Min Speed/Low",
  0.35
};
const nerd::ConfigKey<double> JOYSTICKS_DRIVE_DEADZONE{
  "Joysticks/Drive/Deadzone",
  0.02
};
const nerd::ConfigKey<bool> JOYSTICKS_REVERSE_FORWARD{
  "Joysticks/Drive/Reverse",
  false
};

// Switch Speed
const nerd::ConfigKey<bool> SWITCH_SPEED_PREFERENCES{
  "Joysticks/Low Speed",
  false
};
// End Joysticks

// Launcher values
const nerd::ConfigKey<double> LAUNCHER_CONTROLLER_P{
  "Launcher/Controller/P",
  6e-5
};
const nerd::ConfigKey<double> LAUNCHER_CONTROLLER_I{
  "Launcher/Controller/I",
  0
};
const nerd::ConfigKey<double> LAUNCHER_CONTROLLER_D{
  "Launcher/Controller/D",
  0
};
const nerd::ConfigKey<double> LAUNCHER_MAX_SPEED{
  "Launcher/Controller/Max Speed",
  0.8
};
const nerd::ConfigKey<double> LAUNCHER_MIN_SPEED{
  "Launcher/Controller/Min Speed",
  0.25
};
const nerd::ConfigKey<double> LAUNCHER_CURRENT_SPEED{
  "Launcher/Current Speed",
  5
};
const nerd::ConfigKey<double> LAUNCHER_INTAKE_SPEED{
  "Launcher/Intake Speed",
  5
};
const nerd::ConfigKey<double> LAUNCHER_CONVEYOR_SPEED{
  "Launcher/Conveyor Speed",
  5
};
// End Launcher

// Autonomous PID
const nerd::ConfigKey<double> AUTO_TURN_P{
  "Autonomous/Turn/P",
  0.5
};
const nerd::ConfigKey<double> AUTO_TURN_I{
  "Autonomous/Turn/I",
  0
};
const nerd::ConfigKey<double> AUTO_TURN_D{
  "Autonomous/Turn/D",
  0
};
// End Autonomous PID

// Autonomous Parameters
const nerd::ConfigKey<double> AUTONOMOUS_DRIVE_TOLERANCE {
  "Autonomous/Drive/Tolerance",
  0.25
};
const nerd::ConfigKey<double> AUTONOMOUS_DRIVE_ACCELERATION {
  "Autonomous/Drive/Acceleration",
  8
};
const nerd::ConfigKey<double> AUTONOMOUS_DRIVE_MAX_SPEED {
  "Autonomous/Drive/Max Speed",
  0.8
};
const nerd::ConfigKey<double> AUTONOMOUS_DRIVE_MIN_SPEED {
  "Autonomous/Drive/Min Speed",
  0.25
};
const nerd::ConfigKey<double> AUTONOMOUS_TURN_TOLERANCE {
  "Autonomous/Turn/Tolerance",
  2
};
const nerd::ConfigKey<double> AUTONOMOUS_TURN_MAX_SPEED {
  "Autonomous/Turn/Max Speed",
  0.8
};
const nerd::ConfigKey<double> AUTONOMOUS_TURN_MIN_SPEED {
  "Autonomous/Turn/Min Speed",
  0.25
};
const nerd::ConfigKey<double> AUTONOMOUS_TURN_TIME_ON_TARGET {
  "Autonomous/Turn/Time on Target",
  1
};
// End Autonomous Parameters

// Reel values
const nerd::ConfigKey<double> SET_REEL_SPEED{
  "Joysticks/Reel Speed",
  2
};

// Ramsete
const nerd::ConfigKey<double> FEEDFORWARD_KS {
  "Ramsete/Feed Forward/KS",
  0.1
};

const nerd::ConfigKey<double> FEEDFORWARD_KA {
  "Ramsete/Feed Forward/KA",
  0
};

const nerd::ConfigKey<double> FEEDFORWARD_KV {
  "Ramsete/Feed Forward/KV",
  0.0811
};

const nerd::ConfigKey<double> KP_DRIVE_VELOCITY {
  "Ramsete/Drive/Velocity",
  0.05
};

const nerd::ConfigKey<double> K_MAX_SPEED {
  "Ramsete/Trajectory/Max Speed",
  1
};

const nerd::ConfigKey<double> K_MAX_ACCELERATION {
  "Ramsete/Trajectory/Max Acceleration",
  0.5
};

const nerd::ConfigKey<double> K_RAMSETE_B {
  "Ramsete/Controller/B",
  2
};

const nerd::ConfigKey<double> K_RAMSETE_ZETA {
  "Ramsete/Controller/Zeta",
  0.2
};

const nerd::ConfigKey<double> RAMSETE_DRIVE_MAX_SPEED {
  "Ramsete/Drive/Max Speed",
  0.85
};

const nerd::ConfigKey<double> RAMSETE_DRIVE_MIN_SPEED {
  "Ramsete/Drive/Min Speed",
  0.25
};
// end Ramsete