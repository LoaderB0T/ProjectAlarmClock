#ifndef HOME_SCREEN_h
#define HOME_SCREEN_h

#include <Arduino.h>
#include "ScreenType.h"
#include "CurrentConfig.h"
#include "AlarmState.h"

class ScreenList;

class HomeScreen : public ScreenType
{
public:
  HomeScreen(RgbColorType &bgColor);

private:
  void init();
  void afterDraw();
};

#endif