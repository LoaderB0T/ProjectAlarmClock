#ifndef RECT_TYPE_h
#define RECT_TYPE_h

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>
#include "RgbColorType.h"
#include "Padding.h"

class Rect
{
public:
  Rect(size_t x, size_t y, size_t w, size_t h, RgbColorType &color, void (*touched)() = NULL, Padding *touchPadding = NULL);
  void draw();
  bool checkTouch(size_t tx, size_t ty);

  size_t x;
  size_t y;
  size_t w;
  size_t h;
  void (*touched)();
  Padding *touchPadding;
  RgbColorType &color;

private:
};

#endif