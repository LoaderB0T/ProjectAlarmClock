#ifndef GLOBAL_VARIABLES_h
#define GLOBAL_VARIABLES_h

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <Wire.h>
#include "RTClib.h"
//

//LCD PINS------------------
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

//TOUCHSCREEN PINS--------------------
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 23 // can be a digital pin
#define XP 22 // can be a digital pin

#define TS_MINY 144
#define TS_MINX 100
#define TS_MAXY 814
#define TS_MAXX 874

#define MINPRESSURE 5
#define MAXPRESSURE 1000

//MUSIC PINS---------------------------
#define SHIELD_RESET -1 // VS1053 reset pin (unused!)
#define SHIELD_CS 7     // VS1053 chip select pin (output)
#define SHIELD_DCS 6    // VS1053 Data/command select pin (output)

#define CARDCS 4 // Card chip select pin
#define DREQ 3   // VS1053 Data request, ideally an Interrupt pin

//OTHER DEFINES
#define NUM_LEDS 4
#define LED_DATA_PIN 31
#define LCD_LIGHT_PIN 30
#define RELAY_PIN 32
#define STANDBY_TIME 10
// #define SNOOZE_TIME 60 * 5 // Snooze time in seconds
#define SNOOZE_TIME 5 // Snooze time in seconds

#define TFT_WIDTH 480
#define TFT_HEIGHT 320

#endif