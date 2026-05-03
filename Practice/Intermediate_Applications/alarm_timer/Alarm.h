#pragma once
#include <string>
#include <chrono>

enum class AlarmStatus {
    Active,
    Triggered,
    Disabled
};

enum class RepeatMode {
    Once,
    Daily,
    Weekdays,
    Weekends,
    Custom
};

struct Alarm {
    int id;
    std::string label;
    int hour;
    int minute;
    AlarmStatus status;
    RepeatMode repeatMode;
    int customIntervalMinutes;
    bool snoozeEnabled;
    int snoozeDurationMinutes;

    // Returns minutes from midnight
    int timeInMinutes() const {
        return hour * 60 + minute;
    }

    std::string repeatModeStr() const {
        switch (repeatMode) {
            case RepeatMode::Once: return "Once";
            case RepeatMode::Daily: return "Daily";
            case RepeatMode::Weekdays: return "Weekdays";
            case RepeatMode::Weekends: return "Weekends";
            case RepeatMode::Custom: return "Every " + std::to_string(customIntervalMinutes) + " min";
            default: return "Unknown";
        }
    }

    std::string statusStr() const {
        switch (status) {
            case AlarmStatus::Active: return "Active";
            case AlarmStatus::Triggered: return "Triggered";
            case AlarmStatus::Disabled: return "Disabled";
            default: return "Unknown";
        }
    }
};