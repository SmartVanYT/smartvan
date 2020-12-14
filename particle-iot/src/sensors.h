#pragma once

#include "const.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

class SensorModule : public Executable
{
private:
  bool tmp117_setup_succeeded = true;

public:
  SensorModule()
  {
  }

  void setup();
  void exec() override;

private:
  float readTemperatureF();
};
