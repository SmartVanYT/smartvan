#pragma once

#include "const.h"
#include <TaskManagerIO.h>

class NetworkTimeSyncModule : public Executable
{
private:
  int hoursSinceSync = 0;

public:
  NetworkTimeSyncModule()
  {
  }

  void setup()
  {
    // Currently taskmanagerio cannot schedule out further than 1 hour
    // https://github.com/davetcc/TaskManagerIO/issues/8
    taskManager.scheduleFixedRate(60 * 60, this, TIME_SECONDS);
  }

  void exec() override
  {
    hoursSinceSync++;
    if (hoursSinceSync >= NETWORK_TIME_SYNC_HOURS)
    {
      hoursSinceSync = 0;
      Log.trace("Initiating network time sync");
      Particle.syncTime();
    }
    else
    {
      Log.trace("An hour has passed but not ready to network sync yet");
    }
  }
};
