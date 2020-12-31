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
  taskManager.scheduleFixedRate(30, this, TIME_SECONDS);
}

void ThermostatModule::exec()
{
  if (shouldTriggerRemoteStart())
  {
    viperModule.triggerEngine();
  }
}

int ThermostatModule::commandCallback(String command)
{
  if (command == "off")
  {
    isEnabled = false;
    SVLED.signalThermostatOff();
    SVLED.signalCommandReceived();
    Log.info("Thermostat disabled by remote command");
    return 1;
  }
  else if (command.startsWith("on"))
  {
    // Format => on:{heat|cool}:targetTemp
    // e.g. on:heat:68
    if (command.length() < 9)
    {
      Log.warn("Invalid command" + command);
      return -1;
    }
    targetTemp = parseTargetTemp(command);
    isCooling = parseIsCooling(command);

    if (targetTempIsValid(targetTemp))
    {
      auto hot_or_cold = isCooling ? "cooling" : "heating";
      Log.info(String::format("Thermostat temp set for %s at %f", hot_or_cold, targetTemp));
      isEnabled = true;
      SVLED.signalThermostatOn();
      return 1;
    }
    else
    {
      Log.warn(String::format("Target temp was not valid: %f", targetTemp));
      return -2;
    }
  }

  return -1;
}

bool ThermostatModule::shouldTriggerRemoteStart()
{
  if (!isEnabled)
  {
    return false;
  }

  auto last_reading = sensorModule.getLastReading();
  if (isCooling && last_reading <= targetTemp)
  {
    // Already cool enough
    return false;
  }
  else if (last_reading >= targetTemp)
  {
    // Already warm enough
    return false;
  }

  if (!engine.isEligibleForAutomatedRemoteStart())
  {
    // Already started
    return false;
  }

  Log.trace(String::format("Eligible for remote start to keep temperature of %f closer to %f", last_reading, targetTemp));

  return true;
}
