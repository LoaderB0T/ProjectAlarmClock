#ifndef SCREEN_TYPE_h
#define SCREEN_TYPE_h

#include <Arduino.h>
#include <ArduinoSTL.h>
#include "RgbColorType.h"
#include "Util.h"
#include "Rect.h"
#include "Triangle.h"
#include "TextPrint.h"
#include "TouchArea.h"
#include "Bmp.h"

class ScreenType
{
public:
  ScreenType(RgbColorType &bgColor);
  virtual void init() = 0;
  void draw();
  virtual void afterDraw() = 0;
  bool checkTouch(size_t x, size_t y);
  bool doRetime = false;
  std::vector<Rect> rects;

protected:
  std::vector<Triangle> trias;
  std::vector<Bmp> bmps;
  std::vector<TouchArea> touchAreas;
  std::vector<TextPrint> textPrints;
  RgbColorType &bgColor;

  void addRect(Rect &rect);
  void addTria(Triangle &tria);
  void addBmp(Bmp &bmp);
  void addTouchArea(TouchArea &touchArea);
  void addTextPrint(TextPrint &textPrint);
};

#endif