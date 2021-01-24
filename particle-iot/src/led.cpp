#include "led.h"
#include <TaskManagerIO.h>

class SVLEDHardware;

SVLEDHardware instance;
LEDStatus blinkWhite(RGB_COLOR_WHITE, LED_PATTERN_BLINK, LED_SPEED_FAST, LEDPriority::LED_PRIORITY_CRITICAL);

// We need these static functions to workaround taskManager.scheduleOnce
static void staticTakeControl()
{
  instance.takeControl();
}

void SVLEDHardware::takeControl()
{
  if (LED_OVERRIDE_SYSTEM)
  {
    RGB.control(true);
    RGB.brightness(backgroundBrightness);
    RGB.color(backgroundColor);
  }
}

void SVLEDHardware::releaseControl()
{
  RGB.control(false);
}

void SVLEDHardware::signalSetupComplete()
{
  taskManager.scheduleOnce(
      5, staticTakeControl, TIME_SECONDS);
}

void SVLEDHardware::signalCommandReceived()
{
  releaseControl();
  blinkWhite.setActive(true);
  taskManager.scheduleOnce(
      2, staticTakeControl, TIME_SECONDS);
}

void SVLEDHardware::signalThermostatOn()
{
  backgroundColor = RGB_COLOR_RED;
  backgroundBrightness = 1;
  takeControl();
}

void SVLEDHardware::signalThermostatOff()
{
  backgroundBrightness = 0;
  takeControl();
}

SVLEDHardware &SVLEDHardware::get()
{
  return instance;
}
