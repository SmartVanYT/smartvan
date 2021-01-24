#pragma once

#include "const.h"
#include <TaskManagerIO.h>

class WatchdogModule : public Executable
{
private:
  int hoursSinceSync = 0;

public:
  WatchdogModule()
  {
  }

  void setup();
  void exec() override;
};
