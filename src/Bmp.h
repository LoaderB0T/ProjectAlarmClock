#ifndef BMP_TYPE_h
#define BMP_TYPE_h

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <SD.h>
#include <Adafruit_TFTLCD.h>

class Bmp
{
public:
  Bmp(size_t x, size_t y, String name, void (*touched)());
  void draw();
  bool checkTouch(size_t tx, size_t ty);

private:
  size_t x;
  size_t y;
  size_t w;
  size_t h;
  String name;
  void bmpDraw(String filename, size_t x, size_t y);
  void (*touched)();
};

#endif