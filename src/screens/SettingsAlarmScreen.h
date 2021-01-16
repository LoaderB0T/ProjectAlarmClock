#ifndef HOME_SETTINGS_ALARM_h
#define HOME_SETTINGS_ALARM_h

#include <Arduino.h>
#include "ScreenType.h"
#include "CurrentConfig.h"
#include "AlarmState.h"

class ScreenList;

class SettingsAlarmScreen : public ScreenType
{
public:
  SettingsAlarmScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif