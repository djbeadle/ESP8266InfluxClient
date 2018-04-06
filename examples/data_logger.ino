/********************************
 *
 * ESP8266 to Influx Server
 *     Library Example
 * 
 * Written by Daniel Beadle in 2018
 ********************************/

#include <ESP8266InfluxServer.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

// For the Si7021 temperature sensor:
#include "SparkFun_Si7021_Breakout_Library.h"

/**  
 * InfluxDB Server Settings
 */
const char * host = "192.168.1.152";  // ip or domain name
uint16_t port = 8086;

/**
 * Measurement Settings
 * 
 * Stored in a struct. If you're logging multiple measurements,
 * create multiple Measurement structs.
 */
Measurement basement_fahren = {
  "FiveOhTwo",  // Database name
  "basement",   // Measurement name
  "fahrenheit",      // Field key
  "esp8266-basement2", // Host
  "us-east"     // Region
};

// Initialize the Si7021 Temp & Humidity sensor
Weather sensor;

// For connecting to the Wi-Fi Network
ESP8266WiFiMulti WiFiMulti;

// Create the database object
ESP8266InfluxServer db_net_server = ESP8266InfluxServer(host, port);

float read_temperature()
{
  float humidity = 0;
  float tempf = 0;
  
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()
  tempf = sensor.getTempF();
  
  Serial.print(tempf);            // print the Fahrenheit
  Serial.println(" degrees Fahrenheit,");

  Serial.print( (tempf - 32) * 5 / 9 );  //  convert to Celsius
  Serial.println(" degrees Celsius, ");

  Serial.print(humidity/100);
  Serial.println(" relative humidity,");

  return tempf;
}

void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println("ESP8266-01 Online");

  sensor.begin();

  // Connect to Wi-Fi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Carlton 2: Electric Boogaloo", "IamTheKing");

  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  } 

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  db_net_server.update(basement_fahren, read_temperature());

  // Pause for 60 seconds
  delay(5000);
}