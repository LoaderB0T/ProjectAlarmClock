#include "CurrentConfig.h"

void CurrentConfig::loadScreen(ScreenType *screen)
{
  this->currentScreen = screen;
  this->currentScreen->draw();
  this->currentScreen->afterDraw();
}

size_t CurrentConfig::getDowMondayZero()
{
  int a = this->currentTime.dayOfTheWeek();
  a -= 1;
  if (a < 0)
    a = 6;
  return a;
}