#include "SettingsTimeScreen.h"
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

size_t new_t_h = 0;
size_t new_t_m = 0;

SettingsTimeScreen::SettingsTimeScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

void settingsTimePrintMinute()
{
  prnt(twoDigit(new_t_m), 210, 160, 13, colorWhite, &colorBlack);
}

void settingsTimePrintHour()
{
  prnt(twoDigit(new_t_h), 30, 160, 13, colorWhite, &colorBlack);
}

void settingsTimeAddMinute()
{
  new_t_m++;
  if (new_t_m >= 60)
  {
    new_t_m = 0;
  }
  settingsTimePrintMinute();
}

void settingsTimeAddHour()
{
  new_t_h++;
  if (new_t_h >= 24)
  {
    new_t_h = 0;
  }
  settingsTimePrintHour();
}

void settingsTimeRemMinute()
{
  if (new_t_m == 0)
  {
    new_t_m = 59;
  }
  else
  {
    new_t_m--;
  }
  settingsTimePrintMinute();
}

void settingsTimeRemHour()
{
  if (new_t_h == 0)
  {
    new_t_h = 23;
  }
  else
  {
    new_t_h--;
  }
  settingsTimePrintHour();
}

void settingsTimeSave()
{
  rtc->adjust(DateTime(config->currentTime.year(), config->currentTime.month(), config->currentTime.day(), new_t_h, new_t_m, 0));
  config->loadScreen(screens->screenHome);
}

void settingsTimeBackToSettings()
{
  config->loadScreen(screens->screenSettings);
}

void SettingsTimeScreen::init()
{
  Rect screenSettingsTimeHeading(0, 0, TFT_WIDTH, 80, colorOrange, NULL);
  TextPrint screenSettingsTimeHeadingText(F("Change Time"), TFT_WIDTH / 2, 40, 5, true, colorBlack);
  TextPrint screenSettingsTimeColon(F(":"), TFT_WIDTH / 2 - 36, TFT_HEIGHT / 2 + 55, 14, true, colorWhite);
  this->addRect(screenSettingsTimeHeading);
  this->addTextPrint(screenSettingsTimeHeadingText);
  this->addTextPrint(screenSettingsTimeColon);

  Triangle screenSettingsTimeAddHour(35, 140, 110, -30, colorOrange, settingsTimeAddHour);
  Triangle screenSettingsTimeRemHour(35, TFT_HEIGHT - 50, 110, 30, colorOrange, settingsTimeRemHour);
  Triangle screenSettingsTimeAddMinute(215, 140, 110, -30, colorOrange, settingsTimeAddMinute);
  Triangle screenSettingsTimeRemMinute(215, TFT_HEIGHT - 50, 110, 30, colorOrange, settingsTimeRemMinute);
  this->addTria(screenSettingsTimeAddHour);
  this->addTria(screenSettingsTimeRemHour);
  this->addTria(screenSettingsTimeAddMinute);
  this->addTria(screenSettingsTimeRemMinute);

  Rect screenSettingsTimeConfirm(TFT_WIDTH - 80, 80, 80, (TFT_HEIGHT - 80) / 2, colorGreen, settingsTimeSave);
  Rect screenSettingsTimeCancel(TFT_WIDTH - 80, (TFT_HEIGHT - 80) / 2 + 80, 80, (TFT_HEIGHT - 80) / 2, colorRed, settingsTimeBackToSettings);
  this->addRect(screenSettingsTimeConfirm);
  this->addRect(screenSettingsTimeCancel);
}

void SettingsTimeScreen::afterDraw()
{
  new_t_h = config->currentTime.hour();
  new_t_m = config->currentTime.minute();
  settingsTimePrintHour();
  settingsTimePrintMinute();
}