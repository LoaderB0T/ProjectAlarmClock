#ifndef LIGHT_CONTROL_h
#define LIGHT_CONTROL_h

#include <GlobalVariables.h>

class LightControl
{
public:
  LightControl();
  void light();
  void permanent(bool value);
  void tick();
  bool isOn();

private:
  int lightTimeout;
  bool permanentValue;
};

#endif