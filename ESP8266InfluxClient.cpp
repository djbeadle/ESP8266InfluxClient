#include "ESP8266InfluxClient.h"

/** 
 * Creates a Influx database object.
 * 
 * This is constructor creates it's own instance of WiFiClient. If you're
 * only updating a single database, this should be fine. If you're doing many,
 * then you should use the other constructor and pass in a shared 
 * WiFiClient
 */
ESP8266InfluxClient::ESP8266InfluxClient(
    const char* hostname,
    uint16_t port
 ) :
    hostname(hostname),
    port(port)
{
    client = WiFiClient();
}

/**
 * Constructor using a shared WiFiClient
 */
ESP8266InfluxClient::ESP8266InfluxClient(
    const char* hostname,
    uint16_t port,
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
 *  Measurement measurement
 *  int value
 * 
 * Returns some positive int if successfull.
 */
int ESP8266InfluxClient::update(Measurement measurement, int value)
{
    char* temp = "";
    temp += value;
    update_helper(measurement, temp);
}

/**
 * Sends a single data point to the database.
 * 
 * Requires:
 *  Measurement measurement
 *  float value
 * 
 * Only accurate to 10 places, including the decimal point.
 * Returns some positive int if successfull.
 */
int ESP8266InfluxClient::update(Measurement measurement, float value)
{
    char temp[10];
    sprintf(temp, "%f", value);
    update_helper(measurement, temp);
}

int ESP8266InfluxClient::update_helper(Measurement measurement, char* value)
{
    // Create connection
    if (!client.connect(hostname, port)) {
        Serial.println("connection cfailed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return -1;
    }

    // Build the payload
    String payload = "";
    payload.concat(measurement.measurement_name);
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
    client.print("POST /write?db=");
    client.print(measurement.database);
    client.print(":");
    client.print(this->port);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(this->hostname);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("content-length: ");
    client.println(payload.length());
    client.println("");
    client.println(payload);

    // Read back one line from server
    String line = client.readStringUntil('\r');
    client.stop();
    return line.toInt();
}