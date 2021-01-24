#include "watchdog.h"

static ApplicationWatchdog *wd;

static void watchdogHandler()
{
  // Do as little as possible in this function, preferably just
  // calling System.reset().
  // Do not attempt to Particle.publish(), use Cellular.command()
  // or similar functions. You can save data to a retained variable
  // here safetly so you know the watchdog triggered when you
  // restart.
  // In 2.0.0 and later, RESET_NO_WAIT prevents notifying the cloud of a pending reset
  System.reset(RESET_NO_WAIT);
}

void WatchdogModule::setup()
{
  wd = new ApplicationWatchdog(60s, watchdogHandler, 1536);
  taskManager.scheduleFixedRate(30, this, TIME_SECONDS);
}

void WatchdogModule::exec()
{
  wd->checkin(); // resets the AWDT count
}