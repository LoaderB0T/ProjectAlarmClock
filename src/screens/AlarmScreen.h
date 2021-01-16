#ifndef ALARM_SCREEN_h
#define ALARM_SCREEN_h

#include <Arduino.h>
#include <Adafruit_VS1053.h>
#include "ScreenType.h"
#include "CurrentConfig.h"
#include "AlarmState.h"

class ScreenList;

class AlarmScreen : public ScreenType
{
public:
  AlarmScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif