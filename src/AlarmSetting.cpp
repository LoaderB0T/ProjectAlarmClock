#include "AlarmSetting.h"

AlarmSetting::AlarmSetting(size_t hour, size_t minute, String enabledDays, bool enabled)
{
  this->hour = hour;
  this->minute = minute;
  this->enabled = enabled;
  this->enabledDays.reserve(10);
  this->enabledDays = enabledDays;
}

AlarmSetting::AlarmSetting(const AlarmSetting &oldAlarmSetting)
{
  this->hour = oldAlarmSetting.hour;
  this->minute = oldAlarmSetting.minute;
  this->enabled = oldAlarmSetting.enabled;
  this->enabledDays.reserve(10);
  this->enabledDays = oldAlarmSetting.enabledDays;
}

AlarmSetting::AlarmSetting() : AlarmSetting(0, 0, "", false)
{
}

void AlarmSetting::toggle()
{
  this->enabled = !this->enabled;
}

void AlarmSetting::changeDow(size_t dowIndex, bool enabled)
{
  String newDow;
  for (size_t i = 0; i < 7; i++)
  {
    bool dayIsEnabled = (i + 1) == dowIndex ? enabled : this->isEnabledForDayIndex(i + 1);
    if (dayIsEnabled)
    {
      newDow += String(i + 1);
    }
  }

  enabledDays = newDow;
}

bool AlarmSetting::isEnabledForDayIndex(size_t dayIndex)
{
  return enabledDays.indexOf(String(dayIndex)) > -1;
}

AlarmSetting::operator String(void) const
{
  return "Days: " + enabledDays + " Time: " + String(hour) + ":" + String(minute);
}