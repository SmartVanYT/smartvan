#pragma once

#include "const.h"
#include "sensors/engine.h"
#include "sensors/thermometer.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>

class DataPublisher : public Executable
{
private:
  EngineSensor &engine;
  Thermometer &thermometer;

public:
  DataPublisher(EngineSensor &engine, Thermometer &thermometer) : engine(engine), thermometer(thermometer)
  {
  }

  void setup();
  void exec() override;
};
