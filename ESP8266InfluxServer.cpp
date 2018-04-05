#include "ESP8266InfluxServer.h"

/** 
 * Creates a Influx database object.
 * 
 * This is constructor creates it's own instance of WiFiClient. If you're
 * only updating a single database, this should be fine. If you're doing many,
 * then you should use the other constructor and pass in a shared 
 * WiFiClient
 */
ESP8266InfluxServer::ESP8266InfluxServer(
    const char* hostname,
    uint16_t port
 ) :
    client(WiFiClient()), 
    hostname(hostname),
    port(port)
{}

/**
 * Constructor using a shared WiFiClient
 */
ESP8266InfluxServer::ESP8266InfluxServer(
    const char* hostname,
    uint16_t port
    WiFiClient client
 ) :
    client(client), 
    hostname(hostname),
    port(port)
{}

/**
 * Sends a single data point to the database.
 * 
 * Requires:
 *  char* measurement
 *  char* field_key
 *  int value
 * 
 * Returns some positive int if successfull.
 */
int ESP8266InfluxServer::update(InfluxMeasurement measurement, int value)
{
    // Create connection
    if (!client.connect(hostname, port)) {
        Serial.println("connection cfailed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return -1;
    }

    // [measurement],host=[tag_host],region=[tag_region] [field_key]=[value] 
    // "basement,host=esp8266one,region=us-east cpm=";

    // Build the payload
    String payload = "";
    payload.concat(measurement.measurement);
    payload.concat(",host=");
    payload.concat(measurement.tag_host);
    payload.concat(",region=");
    payload.concat(measurement.tag_region);
    payload.concat(" ");
    payload.concat(measurement.field_key);
    payload.concat("=");
    payload.concat(value);

    // Build the header and send it to the server
    // This will send the request to the server
    client.println("POST /write?db=FiveOhTwo HTTP/1.1");
    client.print("Host: ");
    client.println("192.168.1.152");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("content-length: ");
    client.println(payload.length());
    client.println("");
    client.println(payload);
        
    client.println("POST /write?db=FiveOhTwo HTTP/1.1");
    client.print("Host: ");
    client.println("192.168.1.152");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("content-length: ");
    client.println(payload.length());
    client.println("");
    client.println(payload);

    // Read back one line from server
    String line = client.readStringUntil('\r');
    client.stop();
    return line;
}