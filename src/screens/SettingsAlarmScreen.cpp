#include "SettingsAlarmScreen.h"
#include "ScreenList.h"

extern RgbColorType colorOrange;
extern RgbColorType colorRed;
extern RgbColorType colorGreen;
extern RgbColorType colorBlack;
extern ScreenList *screens;
extern CurrentConfig *config;
extern AlarmState *alarmState;
extern void retime(bool);
extern String twoDigit(size_t);
extern void loadAlarms();
extern String *dotw;
size_t currentAlarmIndex = 0;
Padding alarmPadding(5, 5, 0, 5);

SettingsAlarmScreen::SettingsAlarmScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

void showHomeScreen()
{
  config->loadScreen(screens->screenHome);
}

void settingsAlarmPrintPageNavigation()
{
  RgbColorType pageNextColor = colorOrange;
  RgbColorType pagePrevColor = colorOrange;
  if ((currentAlarmIndex + 1) * 3 < alarmState->alarms.size())
  {
    pageNextColor = colorBlack;
  }
  if (currentAlarmIndex > 0)
  {
    pagePrevColor = colorBlack;
  }
  TextPrint alarmPageNext(">", TFT_WIDTH - 40, TFT_HEIGHT * 3 / 16, 10, true, pageNextColor);
  TextPrint alarmPagePrev("<", TFT_WIDTH - 40, TFT_HEIGHT * 9 / 16, 10, true, pagePrevColor);
  alarmPageNext.draw();
  alarmPagePrev.draw();
}

void drawAlarmDays(AlarmSetting &alarm, size_t index)
{
  for (size_t i = 0; i < 7; i++)
  {
    TextPrint alarmDay(dotw[i], 5 + (43.5 * i), TFT_HEIGHT / 4 * index + 51, 3, false, colorBlack, alarm.isEnabledForDayIndex(i + 1) ? &colorGreen : &colorRed, &alarmPadding);
    alarmDay.draw();
  }
}

void drawAlarm(AlarmSetting &alarm, size_t index)
{
  if (alarm.enabled)
  {
    Rect alarmRect(0, TFT_HEIGHT / 4 * index, TFT_WIDTH - 175, TFT_HEIGHT / 4 - 5, colorGreen, NULL);
    alarmRect.draw();
  }
  else
  {
    Rect alarmRect(0, TFT_HEIGHT / 4 * index, TFT_WIDTH - 175, TFT_HEIGHT / 4 - 5, colorRed, NULL);
    alarmRect.draw();
  }

  TextPrint alarmText(twoDigit(alarm.hour) + F(":") + twoDigit(alarm.minute), (TFT_WIDTH - 175) / 2, TFT_HEIGHT / 4 * index + 25, 5, true, colorBlack, NULL);
  alarmText.draw();

  drawAlarmDays(alarm, index);
}

void drawAlarms()
{
  for (size_t i = 0; i <= 2; i++)
  {
    if (alarmState->alarms.size() >= currentAlarmIndex * 3 + i + 1)
    {
      auto alarm = alarmState->alarms[currentAlarmIndex * 3 + i];
      drawAlarm(alarm, i);
    }
    else
    {
      Rect inexistingAlarmRect(0, TFT_HEIGHT / 4 * i, TFT_WIDTH - 175, TFT_HEIGHT / 4 - 5, colorBlack, NULL);
      inexistingAlarmRect.draw();
    }
  }
}

void settingsAlarmScreenPageNext()
{
  if ((currentAlarmIndex + 1) * 3 < alarmState->alarms.size())
  {
    currentAlarmIndex += 1;
    drawAlarms();
    settingsAlarmPrintPageNavigation();
  }
}

void settingsAlarmScreenPagePrev()
{
  if (currentAlarmIndex > 0)
  {
    currentAlarmIndex -= 1;
    drawAlarms();
    settingsAlarmPrintPageNavigation();
  }
}

void settingsAlarmTouchedAlarm(size_t index)
{
  if (alarmState->alarms.size() <= index)
  {
    return;
  }
  alarmState->alarms[index].toggle();
  drawAlarm(alarmState->alarms[index], index - currentAlarmIndex * 3);
}

void settingsAlarmTouchedAlarm1()
{
  settingsAlarmTouchedAlarm(0 + currentAlarmIndex * 3);
}
void settingsAlarmTouchedAlarm2()
{
  settingsAlarmTouchedAlarm(1 + currentAlarmIndex * 3);
}
void settingsAlarmTouchedAlarm3()
{
  settingsAlarmTouchedAlarm(2 + currentAlarmIndex * 3);
}

void settingsAlarmDeleteAlarm(size_t index)
{
  if (alarmState->alarms.size() > index)
  {
    alarmState->alarms.erase(alarmState->alarms.begin() + index);
    drawAlarms();
  }
}

void settingsAlarmDeleteAlarm1()
{
  settingsAlarmDeleteAlarm(0 + currentAlarmIndex * 3);
}
void settingsAlarmDeleteAlarm2()
{
  settingsAlarmDeleteAlarm(1 + currentAlarmIndex * 3);
}
void settingsAlarmDeleteAlarm3()
{
  settingsAlarmDeleteAlarm(2 + currentAlarmIndex * 3);
}

void settingsAlarmCancelEdit()
{
  loadAlarms();
  config->loadScreen(screens->screenHome);
}

void settingsAlarmSaveEdit()
{
  SD.remove("alarms.txt");
  String tmpAlarm = "";
  for (size_t i = 0; i < alarmState->alarms.size(); i++)
  {
    //Syntax: Activated-Hour-Minute-Days~
    tmpAlarm += (alarmState->alarms[i].enabled ? String("1") : String("0")) + "-" + String(alarmState->alarms[i].hour) + "-" + String(alarmState->alarms[i].minute) + "-" + alarmState->alarms[i].enabledDays + "~";
  }
  Serial.println(tmpAlarm);
  File myFile = SD.open("alarms.txt", FILE_WRITE);
  if (myFile)
  {
    myFile.print(tmpAlarm);
    myFile.close();
  }
  config->loadScreen(screens->screenHome);
}

void settingsAlarmAdd()
{
  config->loadScreen(screens->screenSettingsAddAlarm);
}

void SettingsAlarmScreen::init()
{
  Rect settingsAlarmDeleteAlarmRect1(TFT_WIDTH - 175, TFT_HEIGHT / 4 * 0, 70, TFT_HEIGHT / 4 - 5, colorRed, settingsAlarmDeleteAlarm1);
  Rect settingsAlarmDeleteAlarmRect2(TFT_WIDTH - 175, TFT_HEIGHT / 4 * 1, 70, TFT_HEIGHT / 4 - 5, colorRed, settingsAlarmDeleteAlarm2);
  Rect settingsAlarmDeleteAlarmRect3(TFT_WIDTH - 175, TFT_HEIGHT / 4 * 2, 70, TFT_HEIGHT / 4 - 5, colorRed, settingsAlarmDeleteAlarm3);
  this->addRect(settingsAlarmDeleteAlarmRect1);
  this->addRect(settingsAlarmDeleteAlarmRect2);
  this->addRect(settingsAlarmDeleteAlarmRect3);

  Rect addAlarm(TFT_WIDTH / 3 * 0, TFT_HEIGHT / 4 * 3, TFT_WIDTH / 3 - 2, TFT_HEIGHT / 4 - 5, colorOrange, settingsAlarmAdd);
  Rect backAlarm(TFT_WIDTH / 3 * 1 + 1, TFT_HEIGHT / 4 * 3, TFT_WIDTH / 3 - 2, TFT_HEIGHT / 4 - 5, colorOrange, settingsAlarmCancelEdit);
  Rect saveAlarm(TFT_WIDTH / 3 * 2 + 2, TFT_HEIGHT / 4 * 3, TFT_WIDTH / 3 - 2, TFT_HEIGHT / 4 - 5, colorOrange, settingsAlarmSaveEdit);
  this->addRect(addAlarm);
  this->addRect(backAlarm);
  this->addRect(saveAlarm);

  TextPrint addAlarmText(F("Add"), TFT_WIDTH * 1 / 6 + 5, TFT_HEIGHT - TFT_HEIGHT / 4 / 2, 4, true, colorBlack);
  TextPrint backAlarmText(F("Back"), TFT_WIDTH * 3 / 6 + 8, TFT_HEIGHT - TFT_HEIGHT / 4 / 2, 4, true, colorBlack);
  TextPrint saveAlarmText(F("Save"), TFT_WIDTH * 5 / 6 + 5, TFT_HEIGHT - TFT_HEIGHT / 4 / 2, 4, true, colorBlack);
  this->addTextPrint(addAlarmText);
  this->addTextPrint(backAlarmText);
  this->addTextPrint(saveAlarmText);

  Rect alarmPageNext(TFT_WIDTH - 100, 0, 100, TFT_HEIGHT * 3 / 4 / 2 - 5, colorOrange, settingsAlarmScreenPageNext);
  Rect alarmPagePrev(TFT_WIDTH - 100, TFT_HEIGHT / 4 * 3 / 2, 100, TFT_HEIGHT * 3 / 4 / 2 - 5, colorOrange, settingsAlarmScreenPagePrev);
  this->addRect(alarmPageNext);
  this->addRect(alarmPagePrev);

  TouchArea touchedAlarm1(0, TFT_HEIGHT / 4 * 0, TFT_WIDTH - 175, TFT_HEIGHT / 4 - 5, settingsAlarmTouchedAlarm1);
  TouchArea touchedAlarm2(0, TFT_HEIGHT / 4 * 1, TFT_WIDTH - 175, TFT_HEIGHT / 4 - 5, settingsAlarmTouchedAlarm2);
  TouchArea touchedAlarm3(0, TFT_HEIGHT / 4 * 2, TFT_WIDTH - 175, TFT_HEIGHT / 4 - 5, settingsAlarmTouchedAlarm3);
  this->addTouchArea(touchedAlarm1);
  this->addTouchArea(touchedAlarm2);
  this->addTouchArea(touchedAlarm3);
}

void SettingsAlarmScreen::afterDraw()
{
  currentAlarmIndex = 0;
  drawAlarms();
  settingsAlarmPrintPageNavigation();
}