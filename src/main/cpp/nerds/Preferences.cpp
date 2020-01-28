/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "nerds/Preferences.h"

#include <sstream>

#include <frc/DriverStation.h>
#include <networktables/EntryListenerFlags.h>
#include <networktables/NetworkTableInstance.h>

nerd::Preferences::Preferences() {}

template<>
bool nerd::Preferences::AddListener<double>(std::string key,
    double *const value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (table->ContainsKey(key)) {
        *value = table->GetNumber(key, 0.0);
    } else {
        std::stringstream warning;
        warning << "Key: " << key << " does not exist. (Double)";
        frc::DriverStation::ReportWarning(warning.str());
        return false;
    }

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
        nt::EntryListenerFlags::kUpdate | nt::EntryListenerFlags::kNew);

    return true;
}

template<>
bool nerd::Preferences::AddListener<std::string>(
    std::string key,
    std::string *const value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (table->ContainsKey(key)) {
        *value = table->GetString(key, "");
    } else {
        std::stringstream warning;
        warning << "Key: " << key << " does not exist. (String)";
        frc::DriverStation::ReportWarning(warning.str());
        return false;
    }

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
        nt::EntryListenerFlags::kUpdate | nt::EntryListenerFlags::kNew);

    return true;
}

template<>
bool nerd::Preferences::AddListener<bool>(std::string key,
    bool *const value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (table->ContainsKey(key)) {
        *value = table->GetBoolean(key, false);
    } else {
        std::stringstream warning;
        warning << "Key: " << key << " does not exist. (String)";
        frc::DriverStation::ReportWarning(warning.str());
        return false;
    }

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
        nt::EntryListenerFlags::kUpdate | nt::EntryListenerFlags::kNew);

    return true;
}

template<>
bool nerd::Preferences::AddPreference<double>(std::string key,
    double value,
    bool overwrite) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (!overwrite) {
        if (table->ContainsKey(key)) {
            return false;
        }
    }

    bool success = table->PutNumber(key, value);

    if (success) {
        table->SetPersistent(key);
    }

    return success;
}

template<>
bool nerd::Preferences::AddPreference<std::string>(
    std::string key,
    std::string value,
    bool overwrite) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (!overwrite) {
        if (table->ContainsKey(key)) {
            return false;
        }
    }

    bool success = table->PutString(key, value);

    if (success) {
        table->SetPersistent(key);
    }

    return success;
}

template<>
bool nerd::Preferences::AddPreference<bool>(std::string key,
    bool value,
    bool overwrite) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (!overwrite) {
        if (table->ContainsKey(key)) {
            return false;
        }
    }

    bool success = table ->PutBoolean(key, value);

    if (success) {
        table->SetPersistent(key);
    }

    return success;
}

template<>
double nerd::Preferences::GetPreference<double>(std::string key, double default_value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (table->ContainsKey(key)) {
        return table->GetNumber(key, 0.0);
    } else {
        std::stringstream warning;
        warning << "Key: " << key << " does not exist. (Double)";
        frc::DriverStation::ReportWarning(warning.str());
        return default_value;
    }
}

template<>
std::string nerd::Preferences::GetPreference<std::string>(std::string key, std::string default_value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (table->ContainsKey(key)) {
        return table->GetString(key, "");
    } else {
        std::stringstream warning;
        warning << "Key: " << key << " does not exist. (String)";
        frc::DriverStation::ReportWarning(warning.str());
        return default_value;
    }
}

template<>
bool nerd::Preferences::GetPreference<bool>(std::string key, bool default_value) {
    auto instance = nt::NetworkTableInstance::GetDefault();
    auto table = instance.GetTable("Preference");

    if (table->ContainsKey(key)) {
        return table->GetBoolean(key, false);
    } else {
        std::stringstream warning;
        warning << "Key: " << key << " does not exist. (Bool)";
        frc::DriverStation::ReportWarning(warning.str());
        return default_value;
    } 
}    