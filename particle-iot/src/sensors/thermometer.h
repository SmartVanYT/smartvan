#pragma once

#include "const.h"
#include <SparkFun_TMP117.h>

class Thermometer
{
public:
  void setup();
  float readNewTemperatureF();
  float getLastTemperatureReading();
};
