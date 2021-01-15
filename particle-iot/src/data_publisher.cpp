#include "data_publisher.h"

// Comma separated values
// payload version, timestamp, temp, is_engine_on
static String buildPayload(float temp_f, bool is_engine_on, float voltage)
{
  String ts = String::format("%d", Time.now());
  return "0," +
         ts + "," +
         String::format("%.1f", temp_f) + "," +
         (is_engine_on ? "1" : "0") + "," +
         String::format("%.1f", voltage);
}

void DataPublisher::setup()
{
  taskManager.scheduleFixedRate(DATA_PUBLISH_PERIOD_SECS, this, TIME_SECONDS);
}

void DataPublisher::exec()
{
  float temp = thermometer.readNewTemperatureF();
  float voltage = voltmeter.readVoltageSmoothed();
  auto payload = buildPayload(temp, engine.isEngineOn(), voltage);
  Log.trace("Publish new data payload " + payload);
  Particle.publish("gcp", payload, PRIVATE);
}
