#ifndef ALARM_SETTING_h
#define ALARM_SETTING_h

#include <Arduino.h>
#include "RTClib.h"

class AlarmSetting
{
public:
  AlarmSetting(size_t hour, size_t minute, String enabledDays, bool enabled);
  AlarmSetting(AlarmSetting const &oldAlarmSetting);
  AlarmSetting();
  void toggle();
  void changeDow(size_t dowIndex, bool enabled);
  bool isEnabledForDayIndex(size_t dayIndex);
  bool enabled;
  size_t hour;
  size_t minute;
  DateTime nextDay;
  String enabledDays;
  operator String(void) const;

private:
};

#endif