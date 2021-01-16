#include <Arduino.h>
#include "RgbColorType.h"
#include "GlobalVariables.h"
#include "Util.h"
#include "ScreenList.h"
#include "Padding.h"
#include "LightControl.h"
#include "AlarmState.h"

//INITIALIZING--------------------------------
Adafruit_TFTLCD *tft;
Adafruit_VS1053_FilePlayer *mp3;
TouchScreen *ts;
RTC_DS3231 *rtc;

//VARIABLES---------------------------
String *dotw;
String *long_dotw;

unsigned long previousMillis;
unsigned long timeSinceTouch;
unsigned long timeSinceTouchDown;
unsigned long timeSinceTouchUp;

size_t lastS1;
size_t lastS2;
size_t lastM;
size_t lastH;
size_t lastDa;
size_t lastMo;
size_t lastYe;

Padding *nullPadding;
ScreenList *screens;
CurrentConfig *config;
LightControl *lightControl;
AlarmState *alarmState;

//Util
extern String twoDigit(size_t);
extern void prnt(String, size_t, size_t, size_t, RgbColorType &, RgbColorType *);
extern void retime(bool, bool);
extern void loadAlarms();
extern void calculateNextAlarm();
//Extern
extern RgbColorType colorOrange;
extern RgbColorType colorBlack;
extern RgbColorType colorWhite;

void loadSDCard()
{
  loadAlarms();
}

void setup()
{
  Serial.begin(9600);

  //INITIALIZING--------------------------------
  tft = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
  mp3 = new Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  ts = new TouchScreen(XP, YP, XM, YM, 300);
  rtc = new RTC_DS3231();

  //VARIABLES---------------------------
  dotw = new String[7]{F("Mo"), F("Tu"), F("We"), F("Th"), F("Fr"), F("Sa"), F("Su")};
  long_dotw = new String[7]{F("Monday"), F("Tuesday"), F("Wednesday"), F("Thursday"), F("Friday"), F("Saturday"), F("Sunday")};

  previousMillis = millis();
  timeSinceTouch = 0;
  timeSinceTouchDown = 0;

  lastS1 = 0;
  lastS2 = 0;
  lastM = 0;
  lastH = 0;
  lastDa = 0;
  lastMo = 0;
  lastYe = 0;

  alarmState->isAlarming = false;

  nullPadding = new Padding(0);
  screens = new ScreenList();
  config = new CurrentConfig();
  lightControl = new LightControl();
  alarmState = new AlarmState();

  pinMode(LCD_LIGHT_PIN, OUTPUT);
  digitalWrite(LCD_LIGHT_PIN, HIGH);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  tft->reset();
  uint16_t identifier = tft->readID();
  tft->begin(identifier);
  tft->fillScreen(RgbColorType::rgbToUint(255, 0, 0));
  tft->setRotation(3);

  mp3->begin();
  SD.begin(CARDCS);
  rtc->begin();

  mp3->setVolume(0, 0);
  mp3->useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  loadSDCard();

  config->currentTime = rtc->now();
  calculateNextAlarm();

  config->loadScreen(screens->screenHome);
}

void checkTouch(size_t x, size_t y, size_t z)
{
  timeSinceTouch += millis() - previousMillis;

  if (z > MINPRESSURE && z < MAXPRESSURE)
  {
    lightControl->light();
    timeSinceTouchUp = 0;
    timeSinceTouchDown += millis() - previousMillis;
    if (timeSinceTouchDown > 1000)
    {
      timeSinceTouch = 250;
      timeSinceTouchDown = 950;
    }
    if (timeSinceTouch >= 250)
    {
      size_t nx = tft->width() - map(y, TS_MINX, TS_MAXX, 0, tft->width());
      size_t ny = tft->height() - map(x, TS_MAXY, TS_MINY, 0, tft->height());
      if (config->currentScreen->checkTouch(nx, ny))
      {
        timeSinceTouch = 0;
      }
    }
  }
  else
  {
    timeSinceTouchUp += millis() - previousMillis;
    if (timeSinceTouchUp > 50)
    {
      timeSinceTouchDown = 0;
      timeSinceTouch = 250;
    }
  }
  previousMillis = millis();
}

void loop()
{
  config->currentTime = rtc->now();

  bool isSnoozing = alarmState->snoozeTime > 0;

  retime(config->currentScreen->doRetime, false);

  if (!alarmState->isAlarming && alarmState->alarmFound)
  {
    bool snoozeIsOver = isSnoozing && alarmState->snoozeTime == 0;
    if (config->currentTime.unixtime() > alarmState->nextAlarm.nextDay.unixtime() || snoozeIsOver)
    {
      config->loadScreen(screens->screenAlarm);
    }
  }

  TSPoint p = ts->getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  checkTouch(p.x, p.y, p.z);

  // Serial.println("x: " + String(p.x) + "y: " + String(p.y));

  // Serial.println(String(FreeRam()));
}