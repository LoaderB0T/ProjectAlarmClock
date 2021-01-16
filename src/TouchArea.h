#ifndef TOUCH_AREA_TYPE_h
#define TOUCH_AREA_TYPE_h

#include <Arduino.h>

class TouchArea
{
public:
  TouchArea(size_t x, size_t y, size_t w, size_t h, void (*touchAction)());
  bool checkTouch(size_t x, size_t y);

private:
  size_t x;
  size_t y;
  size_t w;
  size_t h;
  void (*touchAction)();
};

#endif