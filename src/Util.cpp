#include "Util.h"

extern size_t lastS2;
extern size_t lastS1;
extern size_t lastM;
extern size_t lastH;
extern size_t lastDa;
extern size_t lastMo;
extern size_t lastYe;
extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern String *long_dotw;
extern Adafruit_TFTLCD *tft;
extern CurrentConfig *config;
extern LightControl *lightControl;
extern AlarmState *alarmState;

size_t daysInMonth(size_t month_, size_t year_)
{
  if (month_ == 2)
  {
    if (year_ % 4 == 0)
    {
      return 29;
    }
    else
    {
      return 28;
    }
  }
  else
  {
    if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11)
    {
      return 30;
    }
    else
    {
      return 31;
    }
  }
}

String twoDigit(const size_t num)
{
  String backstr = String(num);

  if (backstr.length() < 2)
  {
    backstr = "0" + backstr;
  }

  return backstr;
}

void prnt(String str_, size_t x, size_t y, size_t sz, RgbColorType &color, RgbColorType *bgColor)
{
  tft->setTextSize(sz);
  tft->setTextColor(color.toUint());
  if (bgColor != NULL)
  {
    tft->fillRect(x, y, str_.length() * ((sz - 1) * 6 + 5), sz * 8, bgColor->toUint());
  }
  tft->setCursor(x, y);
  tft->println(str_);
}

void retime(bool printIt, bool instaretime)
{
  bool timeChanged = lastS2 != config->currentTime.second() % 10;
  if (!timeChanged && !instaretime)
  {
    return;
  }

  if (timeChanged)
  {
    lightControl->tick();
    if (alarmState->snoozeTime > 0)
    {
      alarmState->snoozeTime--;
    }
  }

  // if (secondsToAlarm > -1)
  // {
  //   if (secondsToAlarm == 0)
  //   {
  //     secondsToAlarm = -1;
  //     scr_alert();
  //   }
  //   secondsToAlarm--;
  // }
  bool updateS = instaretime;
  bool updateM = instaretime;
  bool updateH = instaretime;
  bool updateDa = instaretime;

  if (lastDa != config->currentTime.day())
  {
    updateDa = true;
  }
  if (lastH != config->currentTime.hour())
  {
    updateH = true;
  }
  if (lastM != config->currentTime.minute())
  {
    updateM = true;
  }
  if (lastS1 != config->currentTime.second() / 10)
  {
    updateS = true;
  }

  lastS1 = config->currentTime.second() / 10;
  lastS2 = config->currentTime.second() % 10;

  lastM = config->currentTime.minute();
  lastH = config->currentTime.hour();

  lastDa = config->currentTime.day();
  lastMo = config->currentTime.month();
  lastYe = config->currentTime.year();

  if (!printIt)
  {
    return;
  }

  if (updateS)
  {
    prnt(twoDigit(lastS1 * 10 + lastS2), 370, 150, 8, colorOrange, &colorBlack);
  }
  else
  {
    prnt(String(lastS2), 418, 150, 8, colorOrange, &colorBlack);
  }

  if (updateM)
  {
    prnt(twoDigit(lastM), 210, 115, 13, colorOrange, &colorBlack);
  }
  if (updateH)
  {
    prnt(twoDigit(lastH), 30, 115, 13, colorOrange, &colorBlack);
  }
  if (!alarmState->isAlarming)
  {
    if (updateDa)
    {
      Rect coverOldDay(90, 0, TFT_WIDTH - 2 * 90, 50, colorBlack);
      coverOldDay.draw();
      prnt(twoDigit(lastDa) + "." + twoDigit(lastMo), 13, tft->height() - 70, 7, colorBlack, &colorOrange);
      prnt(long_dotw[config->getDowMondayZero()], 240 - (long_dotw[config->getDowMondayZero()].length() * 23 / 2), 30, 4, colorOrange, &colorBlack);
    }
  }
}

void loadAlarms()
{
  alarmState->alarms.clear();
  File myFile;
  if (!SD.exists("ALARMS.TXT"))
  {
    myFile = SD.open("ALARMS.TXT", FILE_WRITE);
    //ENABLED-HOUR-MINUTE-DAYDAYDAY-
    myFile.println("-");
  }
  else
  {
    myFile = SD.open("ALARMS.TXT", FILE_READ);

    while (myFile.available())
    {
      String alarmEnabled = myFile.readStringUntil('-');
      size_t alarmHour = myFile.readStringUntil('-').toInt();
      size_t alarmMinute = myFile.readStringUntil('-').toInt();
      String alarmDays = myFile.readStringUntil('~');

      AlarmSetting newAlarm(alarmHour, alarmMinute, alarmDays, alarmEnabled.equals("1"));
      alarmState->alarms.push_back(newAlarm);
    }

    myFile.close();
  }
}

size_t daysToDayOfWeek(int dowIndex)
{
  int currentDow = config->getDowMondayZero() + 1;
  if (dowIndex - currentDow >= 0)
  {
    return (dowIndex - currentDow);
  }
  else
  {
    return (dowIndex - currentDow + 7);
  }
}

void calculateNextAlarm()
{

  DateTime nextAlarm(config->currentTime);
  nextAlarm = nextAlarm + TimeSpan(100, 0, 0, 0);
  AlarmSetting nextAlarmObj;

  alarmState->alarmFound = false;

  if (!alarmState->activated)
  {
    return;
  }

  for (size_t i = 0; i < alarmState->alarms.size(); i++)
  {
    auto _alarm = alarmState->alarms.at(i);
    if (_alarm.enabled)
    {
      alarmState->alarmFound = true;
      break;
    }
  }

  if (!alarmState->alarmFound)
  {
    return;
  }

  for (auto alarm : alarmState->alarms)
  {
    for (int dayIndex = 1; dayIndex <= 7; dayIndex++)
    {
      if (alarm.enabled && alarm.isEnabledForDayIndex(dayIndex))
      {
        DateTime tmpNextAlarm(config->currentTime.year(), config->currentTime.month(), config->currentTime.day(), alarm.hour, alarm.minute, 0);
        tmpNextAlarm = tmpNextAlarm + TimeSpan(daysToDayOfWeek(dayIndex), 0, 0, 0);

        if (nextAlarm.unixtime() > tmpNextAlarm.unixtime() && tmpNextAlarm.unixtime() > config->currentTime.unixtime())
        {
          Serial.println("Next alarm = " + String(alarm));
          nextAlarm = tmpNextAlarm;
          nextAlarmObj = AlarmSetting(alarm);
          nextAlarmObj.nextDay = DateTime(tmpNextAlarm);
        }
      }
    }
  }
  alarmState->nextAlarm = nextAlarmObj;
}