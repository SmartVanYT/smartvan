#include "thermometer.h"
#include <SparkFun_TMP117.h>

// The default address of the device is 0x48 = (GND)
TMP117 tempSensor; // This thing is a singleton anyways, so declare it statically
bool setupSucceeded = false;
float lastReading = NAN;

void Thermometer::setup()
{
  // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
  if (!tempSensor.begin())
  {
    Log.error("TMP117 failed to setup");
  }
  else
  {
    setupSucceeded = true;
  }
}

float Thermometer::readNewTemperatureF()
{
  if (!setupSucceeded)
  {
    return NAN;
  }

  if (!tempSensor.dataReady())
  {
    return NAN;
  }

  lastReading = tempSensor.readTempF();
  return lastReading;
}

float Thermometer::getLastTemperatureReading()
{
  return lastReading;
}