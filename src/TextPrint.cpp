#include "TextPrint.h"

extern Adafruit_TFTLCD *tft;

TextPrint::TextPrint(const String text, size_t x, size_t y, size_t size, bool centerText, RgbColorType &color, RgbColorType *bgColor, Padding *padding) : color(color)
{
  this->x = x;
  this->y = y;
  this->size = size;
  this->text = text;
  this->centerText = centerText;
  this->bgColor = bgColor;
  this->padding = padding;
}

void TextPrint::draw()
{
  tft->setTextSize(size);
  tft->setTextColor(this->color.toUint());
  size_t textWidth = text.length() * ((size - 1) * 6 + 5);
  size_t textHeight = size * 8;
  size_t newX = x;
  size_t newY = y;

  if (centerText)
  {
    newX = x - (textWidth / 2) - 7;
    if (newX < 0)
      newX = 0;
    tft->setCursor(newX, y);
    newY = y - (textHeight / 2);
    if (newY < 0)
      newY = 0;
  }

  if (bgColor != NULL)
  {
    tft->fillRect(newX - padding->l, newY - padding->t, textWidth + padding->l + padding->r, textHeight + padding->t + padding->b, bgColor->toUint());
  }
  tft->setCursor(newX, newY);
  tft->print(text);
}