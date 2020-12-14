#pragma once

#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

#include "const.h"
#include "Sensors.h"
#include "led.h"
#include "viper.h"

class ThermostatModule : Executable
{
private:
  SensorModule &sensorModule;
  ViperModule &viperModule;
  bool isEnabled = false;
  bool isCooling = false;
  float targetTemp = NAN;

public:
  ThermostatModule(SensorModule sensors, ViperModule viper) : sensorModule(sensors), viperModule(viper)
  {
  }

  void setup();
  void exec() override;

private:
  int commandCallback(String command);
};
