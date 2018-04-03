#include "ESP8266Influx.h"

ESP8266Influx::ESP8266Influx(char* hostname, uint16_t port, char* database, char* tag_region, char* tag_host)
{
    client = WiFiClient();
    hostname = hostname;
    port = port;
    database = database;
    tag_region = tag_region;
    tag_host = tag_host;
}

int ESP8266Influx::update(char* measurement, char* field_key, int value)
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
    payload.concat(measurement);
    payload.concat(",host=");
    payload.concat(tag_host);
    payload.concat(",region=");
    payload.concat(tag_region);
    payload.concat(" ");
    payload.concat(field_key);
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

}