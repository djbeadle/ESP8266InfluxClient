#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "ESP8266Influx.h"

/***** INFLUXDB SETTINGS *****/
char * host = "192.168.1.152";  // ip or domain name
uint16_t port = 8086;
char * database = "FiveOhTwo";  // database name
char * tag_host = "esp8266-basement"; // sensor name
char * tag_region = "us-east";  // name of region
/*****************************/

// For connecting to the Wi-Fi Network
ESP8266WiFiMulti WiFiMulti;

// Our database object
ESP8266Influx database1 = ESP8266Influx(host, port, database, tag_region, tag_host);

void setup() {
  Serial.begin(9600);
  Serial.println("ESP8266-01 Online");

  // Connect to Wi-Fi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSID", "PASSWORD");

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
  int CPM = 25;
  database1.update("basement", "cpm", CPM);

  // Pause for 60 seconds
  delay(60000);
}
