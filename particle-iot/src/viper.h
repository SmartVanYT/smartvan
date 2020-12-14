#pragma once

#include "const.h"
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>

class ViperModule
{
public:
  ViperModule()
  {
  }

  void setup()
  {
    pinMode(VIPER_LOCK, OUTPUT);
    pinMode(VIPER_UNLOCK, OUTPUT);
    pinMode(VIPER_REMOTE_START, OUTPUT);
    digitalWrite(VIPER_LOCK, LOW);
    digitalWrite(VIPER_UNLOCK, LOW);
    digitalWrite(VIPER_REMOTE_START, LOW);

    Particle.function("button", &ViperModule::buttonCallback, this);
  }

  // Actions
  void triggerLock()
  {
    momentaryPush(VIPER_LOCK, 200);
  }
  void triggerUnlock()
  {
    momentaryPush(VIPER_UNLOCK, 200);
  }
  void triggerEngine()
  {
    momentaryPush(VIPER_REMOTE_START, 1000);
  }

private:
  static void buttonRelease(int pin)
  {
    digitalWrite(pin, LOW);
  }

  void momentaryPush(int pin, int duration)
  {
    digitalWrite(pin, HIGH);
    auto callback = new ExecWithParameter<int>(&ViperModule::buttonRelease, pin);
    taskManager.scheduleOnce(duration, callback, TIME_MILLIS, true);
  }

  int buttonCallback(String command)
  {
    SVLED.signalCommandReceived();

    if (command == "lock")
    {
      triggerLock();
      return 1;
    }
    else if (command == "unlock")
    {
      triggerUnlock();
      return 1;
    }
    else if (command == "engine")
    {
      triggerEngine();
      return 1;
    }
    return -1;
  }
};
