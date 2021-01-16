#ifndef SETTINGS_TIME_SCREEN_h
#define SETTINGS_TIME_SCREEN_h

#include <Arduino.h>
#include "ScreenType.h"
#include "CurrentConfig.h"

class ScreenList;

class SettingsTimeScreen : public ScreenType
{
public:
  SettingsTimeScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif