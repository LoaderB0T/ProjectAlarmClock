#include "SettingsAddAlarmScreen.h"
#include "ScreenList.h"

extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern RgbColorType colorWhite;
extern RgbColorType colorGreen;
extern RgbColorType colorRed;
extern ScreenList *screens;
extern CurrentConfig *config;
extern AlarmState *alarmState;
extern RTC_DS3231 *rtc;
extern String *dotw;
extern void prnt(String, size_t, size_t, size_t, RgbColorType &, RgbColorType *);
extern String twoDigit(size_t);

AlarmSetting alarm(0, 0, "", true);
Padding settingsAlarmScreenTrianglesPadding(20, 10, 10, 10);

SettingsAddAlarmScreen::SettingsAddAlarmScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

void settingsAddAlarmPrintMinute()
{
  prnt(twoDigit(alarm.minute), 210, 120, 12, colorWhite, &colorBlack);
}

void settingsAddAlarmPrintHour()
{
  prnt(twoDigit(alarm.hour), 30, 120, 12, colorWhite, &colorBlack);
}

void settingsAddAlarmAddMinute()
{
  alarm.minute++;
  if (alarm.minute >= 60)
  {
    alarm.minute = 0;
  }
  settingsAddAlarmPrintMinute();
}

void settingsAddAlarmAddHour()
{
  alarm.hour++;
  if (alarm.hour >= 24)
  {
    alarm.hour = 0;
  }
  settingsAddAlarmPrintHour();
}

void settingsAddAlarmRemMinute()
{
  if (alarm.minute == 0)
  {
    alarm.minute = 59;
  }
  else
  {
    alarm.minute--;
  }
  settingsAddAlarmPrintMinute();
}

void settingsAddAlarmRemHour()
{
  if (alarm.hour == 0)
  {
    alarm.hour = 23;
  }
  else
  {
    alarm.hour--;
  }
  settingsAddAlarmPrintHour();
}

void settingsAddAlarmPrintDay(size_t index);
void settingsAddAlarmToggleDay(size_t index)
{
  bool prevVal = alarm.isEnabledForDayIndex(index + 1);
  alarm.changeDow(index + 1, !prevVal);
  settingsAddAlarmPrintDay(index);
}

void settingsAddAlarmToggleDay0()
{
  settingsAddAlarmToggleDay(0);
}
void settingsAddAlarmToggleDay1()
{
  settingsAddAlarmToggleDay(1);
}
void settingsAddAlarmToggleDay2()
{
  settingsAddAlarmToggleDay(2);
}
void settingsAddAlarmToggleDay3()
{
  settingsAddAlarmToggleDay(3);
}
void settingsAddAlarmToggleDay4()
{
  settingsAddAlarmToggleDay(4);
}
void settingsAddAlarmToggleDay5()
{
  settingsAddAlarmToggleDay(5);
}
void settingsAddAlarmToggleDay6()
{
  settingsAddAlarmToggleDay(6);
}

void settingsAddAlarmPrintDay(size_t index)
{
  bool alarmEnabled = alarm.isEnabledForDayIndex(index + 1);
  Rect dayRect(index * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, alarmEnabled ? colorGreen : colorRed, NULL);
  dayRect.draw();
  prnt(dotw[index], index * (TFT_WIDTH - 80) / 7 + 5, TFT_HEIGHT - 45, 4, colorBlack, NULL);
}

void settingsAddAlarmPrintDays()
{
  for (size_t i = 0; i < 7; i++)
  {
    settingsAddAlarmPrintDay(i);
  }
}

void settingsAddAlarmSave()
{
  AlarmSetting newAlarm(alarm);
  alarmState->alarms.push_back(newAlarm);
  config->loadScreen(screens->screenSettingsAlarm);
}

void settingsAddAlarmBackToAlarmSettings()
{
  config->loadScreen(screens->screenSettingsAlarm);
}

void SettingsAddAlarmScreen::init()
{
  Rect screenSettingsAddAlarmHeading(0, 0, TFT_WIDTH, 80, colorOrange, NULL);
  TextPrint screenSettingsAddAlarmHeadingText(F("Add Alarm"), TFT_WIDTH / 2, 40, 5, true, colorBlack);
  TextPrint screenSettingsAddAlarmColon(F(":"), TFT_WIDTH / 2 - 40, TFT_HEIGHT / 2 + 10, 14, true, colorWhite);
  this->addRect(screenSettingsAddAlarmHeading);
  this->addTextPrint(screenSettingsAddAlarmHeadingText);
  this->addTextPrint(screenSettingsAddAlarmColon);

  Triangle screenSettingsAddAlarmAddHour(50, 105, 80, -20, colorOrange, settingsAddAlarmAddHour, &settingsAlarmScreenTrianglesPadding);
  Triangle screenSettingsAddAlarmRemHour(50, 215, 80, 20, colorOrange, settingsAddAlarmRemHour, &settingsAlarmScreenTrianglesPadding);
  Triangle screenSettingsAddAlarmAddMinute(230, 105, 80, -20, colorOrange, settingsAddAlarmAddMinute, &settingsAlarmScreenTrianglesPadding);
  Triangle screenSettingsAddAlarmRemMinute(230, 215, 80, 20, colorOrange, settingsAddAlarmRemMinute, &settingsAlarmScreenTrianglesPadding);
  this->addTria(screenSettingsAddAlarmAddHour);
  this->addTria(screenSettingsAddAlarmRemHour);
  this->addTria(screenSettingsAddAlarmAddMinute);
  this->addTria(screenSettingsAddAlarmRemMinute);

  Rect screenSettingsTimeConfirm(TFT_WIDTH - 80, 80, 80, (TFT_HEIGHT - 80) / 2, colorGreen, settingsAddAlarmSave);
  Rect screenSettingsTimeCancel(TFT_WIDTH - 80, (TFT_HEIGHT - 80) / 2 + 80, 80, (TFT_HEIGHT - 80) / 2, colorRed, settingsAddAlarmBackToAlarmSettings);
  this->addRect(screenSettingsTimeConfirm);
  this->addRect(screenSettingsTimeCancel);

  TouchArea dayTouchArea0(0 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay0);
  TouchArea dayTouchArea1(1 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay1);
  TouchArea dayTouchArea2(2 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay2);
  TouchArea dayTouchArea3(3 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay3);
  TouchArea dayTouchArea4(4 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay4);
  TouchArea dayTouchArea5(5 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay5);
  TouchArea dayTouchArea6(6 * (TFT_WIDTH - 80) / 7, TFT_HEIGHT - 60, (TFT_WIDTH - 80) / 7, 60, settingsAddAlarmToggleDay6);
  this->addTouchArea(dayTouchArea0);
  this->addTouchArea(dayTouchArea1);
  this->addTouchArea(dayTouchArea2);
  this->addTouchArea(dayTouchArea3);
  this->addTouchArea(dayTouchArea4);
  this->addTouchArea(dayTouchArea5);
  this->addTouchArea(dayTouchArea6);
}

void SettingsAddAlarmScreen::afterDraw()
{
  alarm.changeDow(1, true);
  alarm.changeDow(2, true);
  alarm.changeDow(3, true);
  alarm.changeDow(4, true);
  alarm.changeDow(5, true);
  alarm.hour = config->currentTime.hour();
  alarm.minute = config->currentTime.minute();
  settingsAddAlarmPrintHour();
  settingsAddAlarmPrintMinute();
  settingsAddAlarmPrintDays();
}