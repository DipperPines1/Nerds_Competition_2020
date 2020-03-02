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
  0.0005
};
const nerd::ConfigKey<double> LAUNCHER_CONTROLLER_I{
  "Launcher/Controller/I",
  0
};
const nerd::ConfigKey<double> LAUNCHER_CONTROLLER_D{
  "Launcher/Controller/D",
  0
};
const nerd::ConfigKey<double> LAUNCHER_CONTROLLER_F{
  "Launcher/Controller/F",
  0.00022
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
const nerd::ConfigKey<bool> LAUNCHER_OVERRIDE{
  "Launcher/Override",
  false
};
const nerd::ConfigKey<double> LAUNCHER_TOLERANCE{
  "Launcher/Tolerance",
  50
};
const nerd::ConfigKey<bool> LAUNCHER_UP_TO_SPEED{
  "Launcher/Up to Speed",
  false
};
// End Launcher

// Conveyor
const nerd::ConfigKey<double> LAUNCHER_CONVEYOR_SPEED{
  "Launcher/Conveyor Speed",
  5
};
const nerd::ConfigKey<bool> CONVEYOR_FEED_OVERRIDE{
  "Conveyor/Feed/Override",
  false
};
// End Conveyor

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

// Start Of Vision Parameters
const nerd::ConfigKey<double> VISION_CENTER_X {
  "Vision/Center/X",
  0
};
const nerd::ConfigKey<double> VISION_CENTER_Y {
  "Vision/Center/Y",
  0
};
const nerd::ConfigKey<double> VISION_TURN_MAX_SPEED  {
  "Vision/Turn/Max Speed",
  0
};
const nerd::ConfigKey<double> VISION_TURN_MIN_SPEED  {
  "Vision/Turn/Min Speed",
  0
};
const nerd::ConfigKey<double> VISION_TOLERANCE {
  "Vision/Turn/Tolerence",
  0
};
// End Vision Parameters

// Start Vision PID
const nerd::ConfigKey<double> VISION_PID_P{
  "Vision/PID/P",
  0.5
};
const nerd::ConfigKey<double> VISION_PID_I{
  "Vision/PID/I",
  0
};
const nerd::ConfigKey<double> VISION_PID_D{
  "Vision/PID/D",
  0
};
const nerd::ConfigKey<double> PID_TIME_ON_TARGET{
  "Vision/PID/Timer",
  1
};
// End vision PID

// Reel values
const nerd::ConfigKey<double> SET_REEL_SPEED{
  "Joysticks/Reel Speed",
  2
};

// POV
const nerd::ConfigKey<bool> POV_ENABLED{
  "Joysticks/POV Enabled",
  true
};
// End POV