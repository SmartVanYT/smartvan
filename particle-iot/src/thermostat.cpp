#include "thermostat.h"

bool parseIsCooling(String command)
{
  auto mode = command.substring(3);
  return mode.startsWith("cool");
}

float parseTargetTemp(String command)
{
  auto temp_str = command.substring(8);
  return temp_str.toFloat();
}

bool targetTempIsValid(float temp)
{
  if (isnan(temp))
  {
    return false;
  }

  if (temp < 40.0 || temp > 80.0)
  {
    return false;
  }

  return true;
}

void ThermostatModule::setup()
{
  Particle.function("thermostat", &ThermostatModule::commandCallback, this);
}

void ThermostatModule::exec()
{
}

int ThermostatModule::commandCallback(String command)
{
  if (command == "off")
  {
    isEnabled = false;
    SVLED.signalCommandReceived();
    return 1;
  }
  else if (command.startsWith("on"))
  {
    // Format => on:{heat|cool}:targetTemp
    // e.g. on:heat:68
    if (command.length() < 9)
    {
      Serial.println("Invalid command" + command);
      return -1;
    }
    targetTemp = parseTargetTemp(command);
    isCooling = parseIsCooling(command);

    if (targetTempIsValid(targetTemp))
    {
      auto hot_or_cold = isCooling ? "cooling" : "heating";
      Serial.println(String::format("Thermostat temp set for %s at %f", hot_or_cold, targetTemp));
      isEnabled = true;
      SVLED.signalThermostatOn();
      return 1;
    }
    else
    {
      Serial.println(String::format("Target temp was not valid: %f", targetTemp));
      return -2;
    }
  }

  return -1;
}
