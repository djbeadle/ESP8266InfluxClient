/*************************************************** 
  This is a library for the ESP8266 for logging data
  to an InfluxDB server.

  Tested specifically with this module, https://www.sparkfun.com/products/13678,
  but it should work with any.
  
  Written by Daniel Beadle
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
#endif

#ifndef ESP8266Influx_h

// These are part of the ESP8266 core for the Arduino enviroment
// https://github.com/esp8266/Arduino
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

class ESP8266Influx
{
    public:
        ESP8266Influx(char* hostname, uint16_t port, char* database, char* tag_region, char* tag_host);
        int update(char* measurement, char* field_key, int value);

    private:
        WiFiClient client;
        uint16_t port;
        char* hostname;
        char* database;
        char* tag_region;
        char* tag_host;
};

#endif