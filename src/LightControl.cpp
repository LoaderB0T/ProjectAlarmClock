#include "LightControl.h"

LightControl::LightControl()
{
  this->lightTimeout = STANDBY_TIME;
  this->permanentValue = false;
}

bool LightControl::isOn()
{
  return this->lightTimeout > 0;
}

void LightControl::light()
{
  this->lightTimeout = STANDBY_TIME;
  digitalWrite(LCD_LIGHT_PIN, HIGH);
}

void LightControl::permanent(bool value)
{
  this->lightTimeout = 10;
  this->permanentValue = value;
  if (value)
  {
    digitalWrite(LCD_LIGHT_PIN, HIGH);
  }
}

void LightControl::tick()
{
  if (this->lightTimeout > 0 && !this->permanentValue)
  {
    this->lightTimeout--;
    if (this->lightTimeout == 0)
    {
      digitalWrite(LCD_LIGHT_PIN, LOW);
    }
  }
}