#include "ScreenType.h"

extern Adafruit_TFTLCD *tft;

ScreenType::ScreenType(RgbColorType &bgColor) : bgColor(bgColor)
{
}

void ScreenType::addRect(Rect &rect)
{
  rects.push_back(rect);
}

void ScreenType::addTria(Triangle &tria)
{
  trias.push_back(tria);
}

void ScreenType::addBmp(Bmp &bmp)
{
  bmps.push_back(bmp);
}

void ScreenType::addTouchArea(TouchArea &touchArea)
{
  touchAreas.push_back(touchArea);
}

void ScreenType::addTextPrint(TextPrint &textPrint)
{
  textPrints.push_back(textPrint);
}

void ScreenType::draw()
{
  tft->fillScreen(bgColor.toUint());
  for (size_t i = 0; i < rects.size(); i++)
  {
    rects[i].draw();
  }
  for (size_t i = 0; i < trias.size(); i++)
  {
    trias[i].draw();
  }
  for (size_t i = 0; i < bmps.size(); i++)
  {
    bmps[i].draw();
  }
  for (size_t i = 0; i < textPrints.size(); i++)
  {
    textPrints[i].draw();
  }
}

bool ScreenType::checkTouch(size_t x, size_t y)
{
  for (size_t i = 0; i < touchAreas.size(); i++)
  {
    if (touchAreas[i].checkTouch(x, y))
    {
      return true;
    }
  }
  for (size_t i = 0; i < rects.size(); i++)
  {
    if (rects[i].checkTouch(x, y))
    {
      return true;
    }
  }
  for (size_t i = 0; i < trias.size(); i++)
  {
    if (trias[i].checkTouch(x, y))
    {
      return true;
    }
  }
  for (size_t i = 0; i < bmps.size(); i++)
  {
    if (bmps[i].checkTouch(x, y))
    {
      return true;
    }
  }
  return false;
}