#include "sensors.h"

// The default address of the device is 0x48 = (GND)
TMP117 temp_sensor; // Initalize sensor

// payload version, timestamp, temp
String buildPayload(float tempF)
{
  String ts = String::format("%d", Time.now());
  return "0," + ts + "," + String::format("%.1f", tempF);
}

void SensorModule::setup()
{
  // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
  if (!temp_sensor.begin())
  {
    Serial.println("TMP117 failed to setup");
    tmp117_setup_succeeded = false;
  }

  taskManager.scheduleFixedRate(DATA_PUBLISH_PERIOD_SECS, this, TIME_SECONDS);
}

void SensorModule::exec()
{
  float tempF = readTemperatureF();
  auto payload = buildPayload(tempF);
  Serial.println("Publish new data payload " + payload);
  Particle.publish("gcp", payload, PRIVATE);
}

float SensorModule::readTemperatureF()
{
  if (!tmp117_setup_succeeded)
  {
    return NAN;
  }

  if (!temp_sensor.dataReady())
  {
    return NAN;
  }

  return temp_sensor.readTempF();
}