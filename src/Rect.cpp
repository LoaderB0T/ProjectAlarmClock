#include "Rect.h"

extern Adafruit_TFTLCD *tft;
extern Padding *nullPadding;

Rect::Rect(size_t x, size_t y, size_t w, size_t h, RgbColorType &color, void (*touched)(), Padding *touchPadding) : color(color)
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

void Rect::draw()
{
  tft->fillRect(x, y, w, h, color.toUint());
}

bool Rect::checkTouch(size_t x, size_t y)
{
  if (this->touched != NULL)
  {
    if (x >= this->x - touchPadding->l && x <= this->x + this->w + touchPadding->r && y >= this->y - touchPadding->t && y <= this->y + this->h + touchPadding->b)
    {
      this->touched();
      return true;
    }
  }
  return false;
}