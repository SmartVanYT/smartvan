#pragma once

#include "const.h"
#include "sensors/engine.h"
#include "sensors/thermometer.h"
#include "sensors/voltmeter.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>

class DataPublisher : public Executable
{
private:
  EngineSensor &engine;
  Thermometer &thermometer;
  Voltmeter &voltmeter;

public:
  DataPublisher(EngineSensor &engine, Thermometer &thermometer, Voltmeter &voltmeter)
      : engine(engine), thermometer(thermometer), voltmeter(voltmeter)
  {
  }

  void setup();
  void exec() override;
};
