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


const nerd::ConfigKey<double> JOYSTICK_DRIVE_MAX{
  "Joysticks/Drive/Max Speed",
  1};
const nerd::ConfigKey<double> JOYSTICK_DRIVE_MIN{
  "Joysticks/Drive/Min Speed",
  0.35};
const nerd::ConfigKey<double> JOYSTICKS_TURN_MAX{
  "Joysticks/Turn/Max Speed",
  1};
const nerd::ConfigKey<double> JOYSTICKS_TURN_MIN{
  "Joysticks/Turn/Min Speed",
  0.35};
const nerd::ConfigKey<double> JOYSTICKS_DRIVE_DEADZONE{
  "Joysticks/Drive/Deadzone",
  0.02};
const nerd::ConfigKey<bool> JOYSTICKS_REVERSE_FORWARD{
  "Joysticks/Drive/Reverse",
  false};
  