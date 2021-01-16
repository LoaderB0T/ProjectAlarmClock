#ifndef TEXT_PRINT_TYPE_h
#define TEXT_PRINT_TYPE_h

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>
#include "RgbColorType.h"
#include "Padding.h"

class TextPrint
{
public:
  TextPrint(const String text, size_t x, size_t y, size_t size, bool centerText, RgbColorType &color, RgbColorType *bgColor = NULL, Padding *padding = NULL);
  void draw();

private:
  size_t x;
  size_t y;
  size_t size;
  Padding *padding;
  String text;
  bool centerText;
  RgbColorType &color;
  RgbColorType *bgColor;
};

#endif