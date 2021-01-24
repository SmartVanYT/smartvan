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
#include "sensors/thermometer.h"
#include "sensors/engine.h"
#include "sensors/voltmeter.h"
#include "data_publisher.h"
#include "ntp_sync.h"
#include "thermostat.h"
#include "watchdog.h"

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
Thermometer thermometer;
Voltmeter voltmeter;
ViperModule viper(engine);
NetworkTimeSyncModule ntp;
WatchdogModule watchdog;
ThermostatModule thermostat(thermometer, viper, engine);
DataPublisher data_publisher(engine, thermometer, voltmeter);

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud

  Wire.begin();
  Wire.setClock(400000); // Set clock speed to be the fastest for better communication (fast mode)

  Log.info("Starting SmartVan");

  watchdog.setup();
  thermometer.setup();
  voltmeter.setup();
  viper.setup();
  data_publisher.setup();
  ntp.setup();
  thermostat.setup();

  SVLED.signalSetupComplete();
}

void loop()
{
  taskManager.runLoop();
}