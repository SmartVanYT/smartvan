#pragma once

#include "const.h"
#include "spark_wiring_led.h"
#include "rgbled.h"

using namespace particle;

class SVLEDHardware
{
private:
  int backgroundBrightness;
  int backgroundColor;

public:
  SVLEDHardware()
  {
  }

  static SVLEDHardware &get();
  void signalSetupComplete();
  void signalCommandReceived();
  void signalThermostatOn();
  void signalThermostatOff();

public:
  void takeControl();
  void releaseControl();
};

#define SVLED SVLEDHardware::get()