/*
 * Project particle-iot
 * Description:
 * Author:
 * Date:
 */

#include <SparkFun_TMP117.h>
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <papertrail.h>
#include "const.h"
#include "led.h"
#include "viper.h"
#include "sensors.h"
#include "ntp_sync.h"
#include "thermostat.h"
#include "engine.h"

// SerialLogHandler logHandler;
PapertrailLogHandler papertailHandler(
    PAPERTRAIL_HOST, PAPERTRAIL_PORT, PAPERTRAIL_APP, System.deviceID(),
    LOG_LEVEL_WARN, // By default particle has noisy logs from comm
    {
        {"app", LOG_LEVEL_TRACE}, // We want our logs
    });

#if PLATFORM_ID == 10
#warning "Papertrail logging on the Electron can consume a lot of data and may result in a higher bill."
#endif

EngineSensor engine;
ViperModule viper(engine);
SensorModule sensors(engine);
NetworkTimeSyncModule ntp;
ThermostatModule thermostat(sensors, viper, engine);

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud

  Wire.begin();
  Wire.setClock(400000); // Set clock speed to be the fastest for better communication (fast mode)

  Log.info("Starting SmartVan");

  viper.setup();
  sensors.setup();
  ntp.setup();
  thermostat.setup();

  SVLED.signalSetupComplete();
}

void loop()
{
  taskManager.runLoop();
}