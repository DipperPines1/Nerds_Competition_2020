/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <networktables/TableEntryListener.h>

namespace nerd {

class Preferences {
 public:
  /**
   * @brief Get the Singleton instance of Preferences
   * 
   * @return Preferences& The instance of Preferences
   */
  static Preferences& GetInstance() {
    static Preferences instance;

    return instance;
  }

  // Delete copy constructor and assignment operator
  Preferences(Preferences const&) = delete;
  void operator=(Preferences const&) = delete;

  /**
   * @brief Add listeners to automatically update the value when the specified key changes with the value paired with the key
   * 
   * @tparam T The type of the value
   * @param key A string that specifies a network table entry
   * @param value a pointer to a variable that is updated when the value in the key changes
   * 
   * @return true when a listener is successfully added
   * @return false when a listener is not created
   */
  template<typename T>
  bool AddListener(std::string key, T *const value);

  /**
   * @brief Add a listener on the specified key which will run the function when a change is detected
   * 
   * @param key The key the listener is attached to
   * @param function The function which will run when the key changes
   * @return true The listener has been successfully attached
   * @return false The listener failed to attach
   */
  bool AddFunctionListener(std::string key, nt::TableEntryListener function);

  /**
   * @brief add or update an entry in the preferences table
   * 
   * @tparam T the type of the value
   * @param key A string that specifies a networktable entry
   * @param value The value stored in the networktable entry
   * @param overwrite if true, overwrites preexisting entries with the same key.
   * @return true Successfully created or updated an entry
   * @return false Failed to create or update an entry
   */
  template<typename T>
  bool AddPreference(std::string key, T value, bool overwrite);

  template<typename T>
  T GetPreference(std::string key, T default_value);

 private:
  Preferences();
};

}  // namespace nerd
