#include "Triangle.h"

extern Adafruit_TFTLCD *tft;
extern Padding *nullPadding;

Triangle::Triangle(size_t x, size_t y, size_t w, int h, RgbColorType &color, void (*touched)(), Padding *touchPadding) : color(color)
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->touched = touched;
  if (touchPadding == NULL)
  {
    this->touchPadding = nullPadding;
  }
  else
  {
    this->touchPadding = touchPadding;
  }
}

void Triangle::draw()
{
  tft->fillTriangle(x, y, x + w, y, x + w / 2, y + h, color.toUint());
}

bool Triangle::checkTouch(size_t x, size_t y)
{
  if (this->touched != NULL)
  {
    if (this->h < 0)
    {
      if (x >= this->x - touchPadding->l && x <= this->x + this->w + touchPadding->r && y <= this->y + touchPadding->b && y >= this->y + this->h - touchPadding->t)
      {
        this->touched();
        return true;
      }
    }
    else
    {
      if (x >= this->x - touchPadding->l && x <= this->x + this->w + touchPadding->r && y >= this->y - touchPadding->t && y <= this->y + this->h + touchPadding->b)
      {
        this->touched();
        return true;
      }
    }
  }
  return false;
}