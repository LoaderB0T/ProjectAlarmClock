#ifndef SETTINGS_SCREEN_h
#define SETTINGS_SCREEN_h

#include <Arduino.h>
#include "ScreenType.h"
#include "CurrentConfig.h"

class ScreenList;

class SettingsScreen : public ScreenType
{
public:
  SettingsScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif