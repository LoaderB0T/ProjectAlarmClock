#include "TouchArea.h"

TouchArea::TouchArea(size_t x, size_t y, size_t w, size_t h, void (*touchAction)())
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->touchAction = touchAction;
}

bool TouchArea::checkTouch(size_t x, size_t y)
{
  if (x >= this->x && x <= this->x + this->w && y >= this->y && y <= this->y + this->h)
  {
    touchAction();
    return true;
  }
  return false;
}