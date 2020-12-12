/*
 * Project particle-iot
 * Description:
 * Author:
 * Date:
 */

#include <SparkFun_TMP117.h>

#define VIPER_LOCK D3
#define VIPER_UNLOCK D4
#define VIPER_REMOTE_START D5

// The default address of the device is 0x48 = (GND)
TMP117 temp_sensor; // Initalize sensor

void pushButton(int pin, int duration)
{
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
}

int buttonCallback(String command)
{
  if (command == "lock")
  {
    pushButton(VIPER_LOCK, 200);
    return 1;
  }
  else if (command == "unlock")
  {
    pushButton(VIPER_UNLOCK, 200);
    return 1;
  }
  else if (command == "engine")
  {
    pushButton(VIPER_REMOTE_START, 1000);
    return 1;
  }
  return -1;
}

void setup()
{
  pinMode(VIPER_LOCK, OUTPUT);
  pinMode(VIPER_UNLOCK, OUTPUT);
  pinMode(VIPER_REMOTE_START, OUTPUT);
  digitalWrite(VIPER_LOCK, LOW);
  digitalWrite(VIPER_UNLOCK, LOW);
  digitalWrite(VIPER_REMOTE_START, LOW);

  Particle.function("button", buttonCallback);

  //   Wire.begin();
  Serial.begin(115200);  // Start serial communication at 115200 baud
  Wire.setClock(400000); // Set clock speed to be the fastest for better communication (fast mode)

  Serial.println("Starting SmartVan");
  // if (!temp_sensor.begin()) // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
  // {
  //   Serial.println("Device failed to setup- Freezing code.");
  //   while (1)
  //     ; // Runs forever
  // }
}

void loop()
{
  // Data Ready is a flag for the conversion modes - in continous conversion the dataReady flag should always be high
  // if (temp_sensor.dataReady() == true) // Function to make sure that there is data ready to be printed, only prints temperature values when data is ready
  // {
  //   float tempC = temp_sensor.readTempC();
  //   float tempF = temp_sensor.readTempF();
  //   // Print temperature in °C and °F
  //   Serial.println(); // Create a white space for easier viewing
  //   Serial.print("Temperature in Celsius: ");
  //   Serial.println(tempC);
  //   Serial.print("Temperature in Fahrenheit: ");
  //   Serial.println(tempF);
  //   delay(500); // Delay added for easier readings
  // }
}