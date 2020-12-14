#pragma once

#include "const.h"
#include "engine.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

class SensorModule : public Executable
{
private:
  EngineSensor &engine;
  bool tmp117SetupSucceeded = true;
  float lastReading = NAN;

public:
  SensorModule(EngineSensor &engine) : engine(engine)
  {
  }

  void setup();
  void exec() override;
  float getLastReading();

private:
  float readTemperatureF();
};
