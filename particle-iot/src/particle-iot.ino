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
#include "led.h"
#include "viper.h"
#include "sensors.h"
#include "ntp_sync.h"

ViperModule viper;
SensorModule sensors;
NetworkTimeSyncModule ntp;

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud

  Wire.begin();
  Wire.setClock(400000); // Set clock speed to be the fastest for better communication (fast mode)

  Serial.println("Starting SmartVan");

  viper.setup();
  sensors.setup();
  ntp.setup();

  SVLED.signalSetupComplete();
}

void loop()
{
  taskManager.runLoop();
}