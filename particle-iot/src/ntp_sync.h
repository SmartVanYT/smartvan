#pragma once

#include "const.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <SparkFun_TMP117.h>

class NetworkTimeSyncModule : public Executable
{
private:
  int hours_since_sync = 0;

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
    hours_since_sync++;
    if (hours_since_sync >= NETWORK_TIME_SYNC_HOURS)
    {
      hours_since_sync = 0;
      Serial.println("Initiating network time sync");
      Particle.syncTime();
    }
    else
    {
      Serial.println("An hour has passed but not ready to network sync yet");
    }
  }
};
