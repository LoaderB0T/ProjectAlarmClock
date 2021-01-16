#include "SettingsScreen.h"
#include "ScreenList.h"

extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern ScreenList *screens;
extern CurrentConfig *config;

SettingsScreen::SettingsScreen(RgbColorType &bgColor) : ScreenType(bgColor)
{
}

void settingsShowHomeScreen()
{
  config->loadScreen(screens->screenHome);
}

void settingsShowSettingsTimeScreen()
{
  config->loadScreen(screens->screenSettingsTime);
}

void settingsShowSettingsDateScreen()
{
  config->loadScreen(screens->screenSettingsDate);
}

void SettingsScreen::init()
{
  Rect screenSettingsSetting1(0, (TFT_HEIGHT / 4) * 0, TFT_WIDTH, (TFT_HEIGHT / 4 - 5), colorOrange, settingsShowSettingsTimeScreen);
  Rect screenSettingsSetting2(0, (TFT_HEIGHT / 4) * 1, TFT_WIDTH, (TFT_HEIGHT / 4 - 5), colorOrange, settingsShowSettingsDateScreen);
  Rect screenSettingsSetting3(0, (TFT_HEIGHT / 4) * 2, TFT_WIDTH, (TFT_HEIGHT / 4 - 5), colorOrange, NULL);
  Rect screenSettingsSetting4(0, (TFT_HEIGHT / 4) * 3, TFT_WIDTH, (TFT_HEIGHT / 4 - 5), colorOrange, settingsShowHomeScreen);
  TextPrint screenSettingChangeTheTime(F("Change the time"), TFT_WIDTH / 2, TFT_HEIGHT / 4 * 0 + TFT_HEIGHT / 8, 4, true, colorBlack);
  TextPrint screenSettingChangeTheDate(F("Change the date"), TFT_WIDTH / 2, TFT_HEIGHT / 4 * 1 + TFT_HEIGHT / 8, 4, true, colorBlack);
  TextPrint screenSettingChangeAlarmSound(F("Change alarm sound"), TFT_WIDTH / 2, TFT_HEIGHT / 4 * 2 + TFT_HEIGHT / 8, 4, true, colorBlack);
  TextPrint screenSettingReady(F("Ready"), TFT_WIDTH / 2, TFT_HEIGHT / 4 * 3 + TFT_HEIGHT / 8, 4, true, colorBlack);

  this->addRect(screenSettingsSetting1);
  this->addRect(screenSettingsSetting2);
  this->addRect(screenSettingsSetting3);
  this->addRect(screenSettingsSetting4);
  this->addTextPrint(screenSettingChangeTheTime);
  this->addTextPrint(screenSettingChangeTheDate);
  this->addTextPrint(screenSettingChangeAlarmSound);
  this->addTextPrint(screenSettingReady);
}

void SettingsScreen::afterDraw()
{
}