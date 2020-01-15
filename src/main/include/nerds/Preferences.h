/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <string>

#pragma once
namespace nerd {

class Preferences {
 public:
  /**
   * @brief Get the Singleton instance of Preferences
   * 
   * @return Preferences& The instance of Preferences
   */
  static Preferences& getInstance() {
    static Preferences instance;

    return instance;
  }

  // Delete copy constructor and assignment operator
  Preferences(Preferences const&) = delete;
  void operator=(Preferences const&) = delete;

  template<typename T>
  bool AddListener(std::string key, T* value);
 private:
  Preferences();
};

}  // namespace nerd
