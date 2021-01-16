#ifndef ALARM_STATE_h
#define ALARM_STATE_h

#include <Arduino.h>
#include <ArduinoSTL.h>
#include "RTClib.h"
#include "AlarmSetting.h"

class AlarmState
{
public:
  AlarmState();
  bool isAlarming;
  int snoozeTime;
  bool activated;
  std::vector<AlarmSetting> alarms;
  AlarmSetting nextAlarm;
  bool alarmFound;

private:
};

#endif