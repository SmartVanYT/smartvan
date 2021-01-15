#pragma once

#include "const.h"

class Voltmeter
{
public:
  Voltmeter()
  {
  }

  void setup()
  {
    pinMode(VOLTMETER_PIN, INPUT);
  }

  float readVoltageOnce()
  {
    int adcValue = analogRead(VOLTMETER_PIN);
    float measuredVoltage = 3.3 * adcValue / VOLTMETER_ADC_MAX;
    float dividerRatio = 1.0 * VOLTMETER_R_BOTTOM / (VOLTMETER_R_TOP + VOLTMETER_R_BOTTOM);
    float actualVoltage = measuredVoltage / dividerRatio;

    return (abs(actualVoltage) < VOLTMETER_MAX_BOUND) ? actualVoltage : NAN;
  }

  float readVoltageSmoothed()
  {
    double total = 0.0;
    for (int i = 0; i < VOLTMETER_SAMPLE_COUNT; i++)
    {
      total += readVoltageOnce();
    }
    return total / VOLTMETER_SAMPLE_COUNT;
  }
};
