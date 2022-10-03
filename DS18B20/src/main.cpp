// I Sanjay Kumar, 000811237 certfy that the given work is my own work and no other person 
// code has been used without due acknowledment.


// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;
// check if sensor is connected or not
bool sensorConnected = false;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
uint8_t address[8];

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  Serial.println("\nTemprature Application");
  if (DS18B20.getAddress(address, 0))
  {
    Serial.print("\nFound device with address ");
    for (int i = 0; i < 8; i++)
    {
      Serial.printf("%02X", address[i]);
    }
    sensorConnected = true;
  }
  else
  {
    Serial.println("\nNo DS182B temprature sensor is installed!");
    sensorConnected = false;
  }
  Serial.println(" ");
}

void loop()
{
  while (sensorConnected)
  {
    float fTemp;

    // ask DS18B20 for the current temperature
    DS18B20.requestTemperatures();
    // local variable sets the room condition based on temprature
    String roomConditions = "";

    // fetch the temperature.  We only have 1 sensor, so the index is 0.
    fTemp = DS18B20.getTempCByIndex(0);
    if (fTemp < 10)
    {
      roomConditions = "Cold!";
    }
    else if (fTemp >= 10 and fTemp < 15)
    {
      roomConditions = "Cool";
    }
    else if (fTemp >= 15 and fTemp < 25)
    {
      roomConditions = "Perfect";
    }
    else if (fTemp >= 25 and fTemp < 30)
    {
      roomConditions = "Warm";
    }
    else if (fTemp >= 30 and fTemp < 35)
    {
      roomConditions = "Hot";
    }
    else
    {
      roomConditions = "Too Hot!";
    }

    // print the temp to the USB serial monitor
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + roomConditions);

    // wait 2s (2000ms) before doing this again
    delay(2000);
  }
}