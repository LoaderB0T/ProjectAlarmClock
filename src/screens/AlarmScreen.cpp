#include "AlarmScreen.h"
#include "ScreenList.h"

extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern ScreenList *screens;
extern CurrentConfig *config;
extern AlarmState *alarmState;
extern Adafruit_VS1053_FilePlayer *mp3;
extern LightControl *lightControl;
extern void retime(bool, bool);

AlarmScreen::AlarmScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

// void settingsShowHomeScreen()
// {
//   config->loadScreen(screens->screenHome);
// }

void screenAlarmSnoozeAlarm()
{
  mp3->stopPlaying();
  digitalWrite(RELAY_PIN, LOW);
  lightControl->permanent(false);
  alarmState->snoozeTime = SNOOZE_TIME;
  alarmState->isAlarming = false;
  config->loadScreen(screens->screenHome);
}

void screenAlarmStopAlarm()
{
  mp3->stopPlaying();
  digitalWrite(RELAY_PIN, LOW);
  lightControl->permanent(false);
  alarmState->isAlarming = false;
  config->loadScreen(screens->screenHome);
}

void AlarmScreen::init()
{
  this->doRetime = true;

  Rect heading(0, 0, TFT_WIDTH, TFT_HEIGHT / 4, colorOrange);
  TextPrint headingText(F("Get up!"), TFT_WIDTH / 2, TFT_HEIGHT / 8, 4, true, colorBlack);
  this->addRect(heading);
  this->addTextPrint(headingText);

  Rect snoozeRect(0, TFT_HEIGHT - 80, TFT_WIDTH / 2 - 3, 80, colorOrange, screenAlarmSnoozeAlarm);
  Rect stopRect(TFT_WIDTH / 2 + 3, TFT_HEIGHT - 80, TFT_WIDTH / 2 - 6, 80, colorOrange, screenAlarmStopAlarm);
  this->addRect(snoozeRect);
  this->addRect(stopRect);

  TextPrint snoozeText(F("Snooze"), TFT_WIDTH / 4, TFT_HEIGHT - 40, 4, true, colorBlack);
  TextPrint stopText(F("Stop"), TFT_WIDTH / 4 * 3, TFT_HEIGHT - 40, 4, true, colorBlack);
  this->addTextPrint(snoozeText);
  this->addTextPrint(stopText);
}

void AlarmScreen::afterDraw()
{
  alarmState->isAlarming = true;
  retime(true, true);
  lightControl->permanent(true);
  digitalWrite(RELAY_PIN, HIGH);
  mp3->setVolume(20, 20);
  mp3->startPlayingFile("track01.mp3");
}