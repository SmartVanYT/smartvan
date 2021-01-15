#pragma once

#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

#include "const.h"
#include "led.h"
#include "viper.h"
#include "sensors/thermometer.h"
#include "sensors/engine.h"

class ThermostatModule : Executable
{
private:
  Thermometer &thermometer;
  ViperModule &viperModule;
  EngineSensor &engine;
  bool isEnabled = false;
  bool isCooling = false;
  float targetTemp = NAN;

public:
  ThermostatModule(Thermometer &thermometer, ViperModule &viper, EngineSensor &engine) : thermometer(thermometer), viperModule(viper), engine(engine)
  {
  }

  void setup();
  void exec() override;

private:
  int commandCallback(String command);
  bool shouldTriggerRemoteStart();
};
