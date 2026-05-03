#pragma once
#include "Alarm.h"
#include <vector>
#include <functional>
#include <string>

// Callback type is invoked when an alarm fires
using AlarmCallback = std::function<void(const Alarm&)>;

class AlarmManager {
public:
    AlarmManager();

    // CRUD
    int addAlarm(const Alarm& alarm);
    bool removeAlarm(int id);
    bool toggleAlarm(int id);
    bool editAlarm(int id, const Alarm& updated);
    Alarm* getAlarm(int id);
    const std::vector<Alarm>& getAlarms() const;

    // Tick:: Call once per second from the main loop
    // Returns ID(s) of alarms that fired this tick
    std::vector<int> tick();

    // Snooze: Reschedule a triggered alarm by its snoozeDurationMinutes
    bool snooze(int id);

    // Dismiss: mark an alarm as triggered (or once to disabled)
    bool dismiss(int id);

    // Persistence
    bool saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);

    // Countdown helpers
    // Return seconds until next firing of the alarm (or -1, if disabled/once+triggered)
    long long secondsUntil(const Alarm& alarm) const;

private:
    std::vector<Alarm> alarms_;
    int nextId_;
    
    // Returns ture if the alarm should fire at the given local time
    bool shouldFire(const Alarm& alarm, int hour, int minute, int weekday) const;
    void advanceRepeat(Alarm& alarm);
};