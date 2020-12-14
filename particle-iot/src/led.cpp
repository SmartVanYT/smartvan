#include "led.h"
#include <TaskManagerIO.h>

SVLEDHardware instance;
LEDStatus blinkWhite(RGB_COLOR_WHITE, LED_PATTERN_BLINK, LED_SPEED_FAST, LEDPriority::LED_PRIORITY_CRITICAL);

static void off()
{
  RGB.control(true);
  RGB.brightness(0);
}

static void on()
{
  RGB.brightness(128);
  RGB.control(false);
}

void SVLEDHardware::signalSetupComplete()
{
  taskManager.scheduleOnce(
      5, [] { off(); }, TIME_SECONDS);
}

void SVLEDHardware::signalCommandReceived()
{
  on();
  blinkWhite.setActive(true);
  taskManager.scheduleOnce(
      2, [] { off(); }, TIME_SECONDS);
}

SVLEDHardware &SVLEDHardware::get()
{
  return instance;
}
