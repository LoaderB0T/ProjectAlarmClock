#include "HomeScreen.h"
#include "ScreenList.h"

extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern ScreenList *screens;
extern CurrentConfig *config;
extern void retime(bool, bool);
extern void calculateNextAlarm();
extern String twoDigit(size_t);
extern String *dotw;
extern AlarmState *alarmState;

HomeScreen::HomeScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

void homeScreenPrintNextAlarm()
{
  if (!alarmState->alarmFound)
  {
    return;
  }
  int dow = alarmState->nextAlarm.nextDay.dayOfTheWeek();
  if (dow - 1 < 0)
  {
    dow = 6;
  }
  else
  {
    dow -= 1;
  }
  TextPrint alarmPrint1(dotw[dow] + " " + twoDigit(alarmState->nextAlarm.nextDay.day()) + "." + twoDigit(alarmState->nextAlarm.nextDay.month()), TFT_WIDTH * 3 / 4, TFT_HEIGHT - 65, 4, true, colorBlack);
  TextPrint alarmPrint2(twoDigit(alarmState->nextAlarm.hour) + ":" + twoDigit(alarmState->nextAlarm.minute), TFT_WIDTH * 3 / 4, TFT_HEIGHT - 25, 4, true, colorBlack);
  alarmPrint1.draw();
  alarmPrint2.draw();
  // Serial.println(twoDigit(config->nextAlarm.hour) + ":" + String(config->nextAlarm.minute));
}

void showSettingsScreen()
{
  config->loadScreen(screens->screenSettings);
}

void homeScreenShowAlarmSettingsScreen()
{
  config->loadScreen(screens->screenSettingsAlarm);
}

void homeScreenPrintTopRightCorner()
{
  if (alarmState->snoozeTime > 0)
  {
    Bmp screenHomeBmpSnooze(TFT_WIDTH - 90, 0, F("snooze.bmp"), NULL);
    screenHomeBmpSnooze.draw();
  }
  else
  {
    if (alarmState->activated)
    {
      Bmp screenHomeBmpAlarm(TFT_WIDTH - 90, 0, F("alarm.bmp"), NULL);
      screenHomeBmpAlarm.draw();
    }
    else
    {
      Bmp screenHomeBmpNoAlarm(TFT_WIDTH - 90, 0, F("noalarm.bmp"), NULL);
      screenHomeBmpNoAlarm.draw();
    }
  }
}

void homeScreenTopRightCornerTouched()
{
  if (alarmState->snoozeTime > 0)
  {
    alarmState->snoozeTime = 0;
  }
  else
  {
    alarmState->activated = !alarmState->activated;
    Rect screenHomeRectBotRight(TFT_WIDTH / 2 + 2, 225, TFT_WIDTH / 2 - 2, TFT_HEIGHT - 225, colorOrange);
    screenHomeRectBotRight.draw();
    calculateNextAlarm();
    homeScreenPrintNextAlarm();
  }
  homeScreenPrintTopRightCorner();
}

void HomeScreen::init()
{
  Rect screenHomeRectBotLeft(0, 225, TFT_WIDTH / 2 - 2, TFT_HEIGHT - 225, colorOrange, NULL);
  Rect screenHomeRectBotRight(TFT_WIDTH / 2 + 2, 225, TFT_WIDTH / 2 - 2, TFT_HEIGHT - 225, colorOrange, homeScreenShowAlarmSettingsScreen);
  Bmp screenHomeBmpSettings(0, 0, F("settings.bmp"), showSettingsScreen);
  TouchArea screenHomeTopRightTouch(TFT_WIDTH - 90, 0, 90, 90, homeScreenTopRightCornerTouched);
  TextPrint colonText(":", 157, 115, 14, false, colorOrange);

  this->addRect(screenHomeRectBotLeft);
  this->addRect(screenHomeRectBotRight);
  this->addBmp(screenHomeBmpSettings);
  this->addTextPrint(colonText);
  this->addTouchArea(screenHomeTopRightTouch);
  this->doRetime = true;
}

void HomeScreen::afterDraw()
{
  retime(true, true);
  homeScreenPrintTopRightCorner();
  calculateNextAlarm();
  homeScreenPrintNextAlarm();
}