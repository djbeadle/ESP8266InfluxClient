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

#ifndef ESP8266InfluxClient_h
#define ESP8266InfluxClient_h

// These are part of the ESP8266 core for the Arduino enviroment
// https://github.com/esp8266/Arduino
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

struct Measurement {
    char* database;
    char* measurement_name;
    char* field_key;
    char* tag_host;
    char* tag_region;
};

class ESP8266InfluxClient
{
    public:
        ESP8266InfluxClient(
            const char* hostname,
            uint16_t port
        );

        int update(
            Measurement measurement,
            int value
        );

        int update(
            Measurement measurement,
            float value
        );

    private:
        uint16_t port;
        const char* hostname;
        
        int update_helper(
            Measurement measurement,
            char* value
        );

};

#endif