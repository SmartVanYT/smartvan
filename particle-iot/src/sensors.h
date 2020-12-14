#pragma once

#include "const.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

class SensorModule : public Executable
{
private:
  bool tmp117SetupSucceeded = true;
  float lastReading = NAN;

public:
  SensorModule()
  {
  }

  void setup();
  void exec() override;
  float getLastReading();

private:
  float readTemperatureF();
};
