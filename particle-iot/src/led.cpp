#include "led.h"
#include <TaskManagerIO.h>

SVLEDHardware instance;
LEDStatus blinkWhite(RGB_COLOR_WHITE, LED_PATTERN_BLINK, LED_SPEED_FAST, LEDPriority::LED_PRIORITY_CRITICAL);

static void takeControl()
{
  RGB.control(true);
  RGB.brightness(0);
}

static void releaseControl()
{
  RGB.brightness(128);
  RGB.control(false);
}

void SVLEDHardware::signalSetupComplete()
{
  taskManager.scheduleOnce(
      5, [] { takeControl(); }, TIME_SECONDS);
}

void SVLEDHardware::signalCommandReceived()
{
  releaseControl();
  blinkWhite.setActive(true);
  taskManager.scheduleOnce(
      2, [] { takeControl(); }, TIME_SECONDS);
}

void SVLEDHardware::signalThermostatOn()
{
  takeControl();
  RGB.brightness(64);
  RGB.color(RGB_COLOR_RED);
}

SVLEDHardware &SVLEDHardware::get()
{
  return instance;
}
