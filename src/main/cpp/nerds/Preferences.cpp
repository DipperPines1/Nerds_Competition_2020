/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "nerds/Preferences.h"

#include "networktables/NetworkTableInstance.h"
#include "networktables/EntryListenerFlags.h"

nerd::Preferences::Preferences() {}

template<>
bool nerd::Preferences::AddListener<double>(std::string key, double* value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preferences");

    table->AddEntryListener(
        key,
        [value] (
            auto table,
            auto name,
            auto entry,
            auto new_value,
            int flag) -> void {
            *value = new_value->GetDouble();
            },
        nt::EntryListenerFlags::kUpdate | nt::EntryListenerFlags::kLocal);

    return true;
}

template<>
bool nerd::Preferences::AddListener<std::string>(
    std::string key,
    std::string* value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preferences");

    table->AddEntryListener(
        key,
        [value] (
            auto table,
            auto name,
            auto entry,
            auto new_value,
            int flag) -> void {
                *value = new_value->GetString();
            },
        nt::EntryListenerFlags::kUpdate | nt::EntryListenerFlags::kLocal);

    return true;
    }

template<>
bool nerd::Preferences::AddListener<bool>(std::string key, bool* value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preferences");

    table->AddEntryListener(
        key,
        [value] (
            auto table,
            auto name,
            auto entry,
            auto new_value,
            int flag) -> void {
                *value = new_value->GetBoolean();
            },
        nt::EntryListenerFlags::kUpdate | nt::EntryListenerFlags::kLocal);

    return true;
    }
