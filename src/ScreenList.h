#ifndef SCREEN_LIST_h
#define SCREEN_LIST_h

#include "ScreenType.h"
#include "screens/HomeScreen.h"
#include "screens/SettingsScreen.h"
#include "screens/SettingsTimeScreen.h"
#include "screens/SettingsDateScreen.h"
#include "screens/SettingsAlarmScreen.h"
#include "screens/SettingsAddAlarmScreen.h"
#include "screens/AlarmScreen.h"

class ScreenList
{
public:
  ScreenList()
  {
    HomeScreen *screenHome = new HomeScreen(*new RgbColorType(0, 0, 0));
    SettingsScreen *screenSettings = new SettingsScreen(*new RgbColorType(0, 0, 0));
    SettingsTimeScreen *screenSettingsTime = new SettingsTimeScreen(*new RgbColorType(0, 0, 0));
    SettingsDateScreen *screenSettingsDate = new SettingsDateScreen(*new RgbColorType(0, 0, 0));
    SettingsAlarmScreen *screenSettingsAlarm = new SettingsAlarmScreen(*new RgbColorType(0, 0, 0));
    SettingsAddAlarmScreen *screenSettingsAddAlarm = new SettingsAddAlarmScreen(*new RgbColorType(0, 0, 0));
    AlarmScreen *screenAlarm = new AlarmScreen(*new RgbColorType(0, 0, 0));

    this->screenHome = screenHome;
    this->screenSettings = screenSettings;
    this->screenSettingsTime = screenSettingsTime;
    this->screenSettingsDate = screenSettingsDate;
    this->screenSettingsAlarm = screenSettingsAlarm;
    this->screenSettingsAddAlarm = screenSettingsAddAlarm;
    this->screenAlarm = screenAlarm;

    this->screenHome->init();
    this->screenSettings->init();
    this->screenSettingsTime->init();
    this->screenSettingsDate->init();
    this->screenSettingsAlarm->init();
    this->screenSettingsAddAlarm->init();
    this->screenAlarm->init();
  }

  ScreenType *screenHome;
  ScreenType *screenSettings;
  ScreenType *screenSettingsTime;
  ScreenType *screenSettingsDate;
  ScreenType *screenSettingsAlarm;
  ScreenType *screenSettingsAddAlarm;
  ScreenType *screenAlarm;
};

#endif