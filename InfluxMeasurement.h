#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
#endif

#ifndef InfluxMeasurement_h

class InfluxMeasurement
{
    private:
        char* database;
        char* tag_region;
        char* tag_host;
        char* measurement;
        char* field_key;

    public:
        InfluxMeasurement(
            const char* database,
            const char* tag_region,
            const char* tag_host,
            const char* measurement,
            const char* field_key
        );
};

#endif