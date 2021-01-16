#include "SettingsDateScreen.h"
#include "ScreenList.h"

extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern RgbColorType colorWhite;
extern RgbColorType colorGreen;
extern RgbColorType colorRed;
extern ScreenList *screens;
extern CurrentConfig *config;
extern RTC_DS3231 *rtc;
extern void prnt(String, size_t, size_t, size_t, RgbColorType &, RgbColorType *);
extern String twoDigit(size_t);
extern size_t daysInMonth(size_t, size_t);

size_t new_d_d = 0;
size_t new_d_m = 0;
size_t new_d_y = 0;

SettingsDateScreen::SettingsDateScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

void settingsDatePrintDay()
{
  prnt(twoDigit(new_d_d), 10, 130, 9, colorOrange, &colorBlack);
}

void settingsDatePrintMonth()
{
  prnt(twoDigit(new_d_m), 130, 130, 9, colorOrange, &colorBlack);
}

void settingsDatePrintYear()
{
  prnt(String(new_d_y), 250, 130, 9, colorOrange, &colorBlack);
}

void settingsDateAddDay()
{
  new_d_d++;
  if (new_d_d > daysInMonth(new_d_m, new_d_y))
  {
    new_d_d = 1;
  }
  settingsDatePrintDay();
}

void settingsDateRemDay()
{
  new_d_d--;
  if (new_d_d < 1)
  {
    new_d_d = daysInMonth(new_d_m, new_d_y);
  }
  settingsDatePrintDay();
}

void settingsDateAddMonth()
{
  new_d_m++;
  if (new_d_m > 12)
  {
    new_d_m = 1;
  }
  settingsDatePrintMonth();
  if (new_d_d > daysInMonth(new_d_m, new_d_y))
  {
    new_d_d = daysInMonth(new_d_m, new_d_y);
    settingsDatePrintDay();
  }
}

void settingsDateRemMonth()
{
  new_d_m--;
  if (new_d_m < 1)
  {
    new_d_m = 12;
  }
  settingsDatePrintMonth();
  if (new_d_d > daysInMonth(new_d_m, new_d_y))
  {
    new_d_d = daysInMonth(new_d_m, new_d_y);
    settingsDatePrintDay();
  }
}

void settingsDateAddYear()
{
  new_d_y++;
  if (new_d_y > 9999)
  {
    new_d_y = 2000;
  }
  settingsDatePrintYear();
  if (new_d_d > daysInMonth(new_d_m, new_d_y))
  {
    new_d_d = daysInMonth(new_d_m, new_d_y);
    settingsDatePrintDay();
  }
}

void settingsDateRemYear()
{
  new_d_y--;
  if (new_d_y < 2000)
  {
    new_d_y = 9999;
  }
  settingsDatePrintYear();
  if (new_d_d > daysInMonth(new_d_m, new_d_y))
  {
    new_d_d = daysInMonth(new_d_m, new_d_y);
    settingsDatePrintDay();
  }
}

void settingsDateSave()
{
  rtc->adjust(DateTime(new_d_y, new_d_m, new_d_d, config->currentTime.hour(), config->currentTime.minute(), config->currentTime.second()));
  config->loadScreen(screens->screenHome);
}

void settingsDateBackToSettings()
{
  config->loadScreen(screens->screenSettings);
}

void SettingsDateScreen::init()
{
  Rect screenSettingsDateHeading(0, 0, TFT_WIDTH, 80, colorOrange, NULL);
  TextPrint screenSettingsDateHeadingText(F("Change Date"), TFT_WIDTH / 2, 40, 5, true, colorBlack);
  // TextPrint screenSettingsDatePoint1(F(":"), TFT_WIDTH / 2, TFT_HEIGHT / 2, 14, true, colorWhite, NULL);
  this->addRect(screenSettingsDateHeading);
  this->addTextPrint(screenSettingsDateHeadingText);
  // screenSettingsTime.addTextPrint(screenSettingsDatePoint1);

  Triangle screenSettingsDateAddDay(20, 110, 75, -25, colorOrange, settingsDateAddDay);
  Triangle screenSettingsDateRemDay(20, TFT_HEIGHT - 110, 75, 25, colorOrange, settingsDateRemDay);
  Triangle screenSettingsDateAddMonth(140, 110, 75, -25, colorOrange, settingsDateAddMonth);
  Triangle screenSettingsDateRemMonth(140, TFT_HEIGHT - 110, 75, 25, colorOrange, settingsDateRemMonth);
  Triangle screenSettingsDateAddYear(315, 110, 75, -25, colorOrange, settingsDateAddYear);
  Triangle screenSettingsDateRemYear(315, TFT_HEIGHT - 110, 75, 25, colorOrange, settingsDateRemYear);
  this->addTria(screenSettingsDateAddDay);
  this->addTria(screenSettingsDateRemDay);
  this->addTria(screenSettingsDateAddMonth);
  this->addTria(screenSettingsDateRemMonth);
  this->addTria(screenSettingsDateAddYear);
  this->addTria(screenSettingsDateRemYear);

  Rect screenSettingsDateConfirm(0, TFT_HEIGHT - 80, TFT_WIDTH / 2, 80, colorGreen, settingsDateSave);
  Rect screenSettingsDateCancel(TFT_WIDTH / 2, TFT_HEIGHT - 80, TFT_WIDTH / 2, 80, colorRed, settingsDateBackToSettings);
  this->addRect(screenSettingsDateConfirm);
  this->addRect(screenSettingsDateCancel);
}

void SettingsDateScreen::afterDraw()
{
  new_d_d = config->currentTime.day();
  new_d_m = config->currentTime.month();
  new_d_y = config->currentTime.year();
  settingsDatePrintDay();
  settingsDatePrintMonth();
  settingsDatePrintYear();
}