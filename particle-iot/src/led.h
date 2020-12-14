#pragma once

#include "const.h"
#include "spark_wiring_led.h"
#include "rgbled.h"

using namespace particle;

class SVLEDHardware
{
public:
  SVLEDHardware()
  {
  }

  static SVLEDHardware &get();
  void signalSetupComplete();
  void signalCommandReceived();
};

#define SVLED SVLEDHardware::get()