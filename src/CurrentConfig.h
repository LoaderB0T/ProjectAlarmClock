#ifndef CURRENT_CONFIG_h
#define CURRENT_CONFIG_h

#include <ArduinoSTL.h>
#include "RTClib.h"
#include "ScreenType.h"

class ScreenType;

class CurrentConfig
{
public:
  DateTime currentTime;
  ScreenType *currentScreen;
  void loadScreen(ScreenType *screen);
  size_t getDowMondayZero();

private:
};

#endif