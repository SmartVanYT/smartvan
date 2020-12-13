/*
 * Project particle-iot
 * Description:
 * Author:
 * Date:
 */

#include <SparkFun_TMP117.h>
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include "const.h"
#include "viper.h"
#include "sensors.h"

ViperModule viper;
SensorModule sensors;

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud

  Wire.begin();
  Wire.setClock(400000); // Set clock speed to be the fastest for better communication (fast mode)

  Serial.println("Starting SmartVan");

  viper.setup();
  sensors.setup();

  taskManager.scheduleFixedRate(
      RESYNC_PARTICLE_NTP_SECS, [] { Particle.syncTime(); },
      TIME_SECONDS);
  taskManager.scheduleFixedRate(
      15, [] { Serial.println("Keepalive"); },
      TIME_SECONDS);
}

void loop()
{
  taskManager.runLoop();
}