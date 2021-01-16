#ifndef SETTINGS_ADD_ALARM_SCREEN_h
#define SETTINGS_ADD_ALARM_SCREEN_h

#include <Arduino.h>
#include "ScreenType.h"
#include "CurrentConfig.h"
#include "AlarmState.h"
#include <algorithm>

class ScreenList;

class SettingsAddAlarmScreen : public ScreenType
{
public:
  SettingsAddAlarmScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif