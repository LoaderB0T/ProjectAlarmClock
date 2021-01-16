#ifndef TRIANGLE_TYPE_h
#define TRIANGLE_TYPE_h

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>
#include "RgbColorType.h"
#include "Padding.h"

class Triangle
{
public:
  Triangle(size_t x, size_t y, size_t w, int h, RgbColorType &color, void (*touched)() = NULL, Padding *touchPadding = NULL);
  void draw();
  bool checkTouch(size_t tx, size_t ty);

private:
  size_t x;
  size_t y;
  size_t w;
  int h;
  void (*touched)();
  Padding *touchPadding;
  RgbColorType &color;
};

#endif