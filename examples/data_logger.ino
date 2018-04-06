/*
 ESP8266 Influx Client Library
 By: Daniel Beadle
 Date: April 6th, 2018
 
 This is an ESP8266 library for easily logging data to an InfluxDB server!
 
 This Library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This Library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 For a copy of the GNU General Public License, see
 <http://www.gnu.org/licenses/>.
 */

// Libraries required for networking on the ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

// This library, woo!
#include <ESP8266InfluxClient.h>

// For the Si7021 temperature sensor:
#include "SparkFun_Si7021_Breakout_Library.h"

/**********************
 * USER SETTINGS HERE *
 **********************/
// Set your Wi-Fi details here
const char *ssid ="Linksys";
const char *password ="SuperFastInternet42";

// Set the details of your InfluxDB server here
const char * host = "192.168.1.143";  // ip or domain name
uint16_t port = 8086; // Set the port your server is listening for data on. Default is 8086

// Measurement Settings
// These are stored in a struct. If you're logging multiple measurements,
// create multiple structs.
Measurement bedroom_temp = {
  "my_house_data",  // Database name
  "bedroom",   // Measurement name
  "fahrenheit",      // Field key
  "esp8266-bedroom-1", // Host name (A name or unique id for the sensor)
  "us-east"     // Region
};

// Initialize the Si7021 Temp & Humidity sensor
Weather sensor;

// For connecting to the Wi-Fi Network
ESP8266WiFiMulti WiFiMulti;

// Create the database object
ESP8266InfluxClient influx_server = ESP8266InfluxClient(host, port);

float read_temperature()
{
  // Measure Temperature from the HTU21D or Si7021
  float tempf = 0;
  tempf = sensor.getTempF();
  
  Serial.print(tempf);            // print the Fahrenheit
  Serial.println(" degrees Fahrenheit,");

  return tempf;
}

void setup() {
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
  // Update the server!
  // If the value returned is >= 0, then it was a success!
  influx_server.update(bedroom_temp, read_temperature());

  // Pause for 60 seconds
  delay(60000);
}