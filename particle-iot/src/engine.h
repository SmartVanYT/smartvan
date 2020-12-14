#pragma once

#include "const.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>

class EngineSensor : Executable
{
private:
  // Note: this is a best guess for now since we don't yet have hooks into the CAN bus
  bool engineOn = false;
  int remoteStarts = 0;
  long remoteStartEndTime = 0;
  long pendingTaskId = 0;

public:
  EngineSensor() : engineOn(false), remoteStarts(0), remoteStartEndTime(0), pendingTaskId(0)
  {
  }

  // Call me when remote start is triggered
  void remoteStartTriggered()
  {
    Serial.println("Remote start triggered");

    if (engineOn)
    {
      remoteStartOff();
      if (pendingTaskId)
      {
        taskManager.cancelTask(pendingTaskId);
        pendingTaskId = 0;
      }

      Serial.println("Engine was on so we turned it off");
    }
    else
    {
      engineOn = true;
      remoteStarts++;

      pendingTaskId = taskManager.scheduleFixedRate(VIPER_REMOTE_START_DURATION_SECS, this, TIME_SECONDS);

      Serial.println("Engine was off so we turned it on");
    }
  }

  bool isEngineOn()
  {
    return engineOn;
  }

  bool isEligibleForAutomatedRemoteStart()
  {
    if (isEngineOn())
    {
      Serial.println("Not eligible because engine is on");
      return false;
    }

    if (remoteStarts > VIPER_REMOTE_START_MAX_STARTS_PER_SESSION)
    {
      Serial.println("Not eligible due to remote starts");
      Serial.println(String::format("%d", remoteStarts));
      return false;
    }

    // This supposedly prevents overflow after 50 days of uptime
    if ((remoteStartEndTime > 0) && (unsigned long)(millis() - remoteStartEndTime) < (VIPER_REMOTE_START_DELAY_UNTIL_NEXT_SECS * 1000))
    {
      Serial.println("Not eligible due to time");
      Serial.println(String::format("%lu vs %lu", millis() - remoteStartEndTime, VIPER_REMOTE_START_DELAY_UNTIL_NEXT_SECS * 1000));
      return false;
    }

    return true;
  }

  void exec() override
  {
    if (engineOn)
    {
      Serial.println("Engine should be turning off around now due to timeout");
      remoteStartOff();
    }
    else
    {
      Serial.println("ERR Engine have been on!");
    }
  }

private:
  void remoteStartOff()
  {
    engineOn = false;
    remoteStartEndTime = millis();
  }
};