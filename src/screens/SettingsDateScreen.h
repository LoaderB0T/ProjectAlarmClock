#ifndef SETTINGS_DATE_SCREEN_h
#define SETTINGS_DATE_SCREEN_h

#include <Arduino.h>
#include "ScreenType.h"
#include "CurrentConfig.h"

class ScreenList;

class SettingsDateScreen : public ScreenType
{
public:
  SettingsDateScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif