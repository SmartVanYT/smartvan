#pragma once

#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

#include "const.h"
#include "sensors.h"
#include "led.h"
#include "viper.h"
#include "engine.h"

class ThermostatModule : Executable
{
private:
  SensorModule &sensorModule;
  ViperModule &viperModule;
  EngineSensor &engine;
  bool isEnabled = false;
  bool isCooling = false;
  float targetTemp = NAN;

public:
  ThermostatModule(SensorModule &sensors, ViperModule &viper, EngineSensor &engine) : sensorModule(sensors), viperModule(viper), engine(engine)
  {
  }

  void setup();
  void exec() override;

private:
  int commandCallback(String command);
  bool shouldTriggerRemoteStart();
};
