#include "InfluxMeasurement.h"

/**
 * Specifies which measurement and which field of that measurement is
 * going to be updated.
 */ 
InfluxMeasurement::InfluxMeasurement(
    const char* database,
    const char* tag_region,
    const char* tag_host,
    const char* measurement,
    const char* field_key
) :
    database(database),
    tag_region(tag_region),
    tag_host(tag_host),
    measurement(measurement),
    field_key(field_key)
}