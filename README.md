# ESP8266InfluxClient

A simple way to log data from your ESP8266 to an InfluxDB server using the [HTTP API](https://docs.influxdata.com/influxdb/v1.5/guides/writing_data/#writing-data-using-the-http-api). Designed for use in the ESP8266 Core for Arduino enviroment. 

Does it work? It seems to! **Please open an issue / contribute a pull request if you have fixes, features, optomizations, issues, etc**.

#TODO:
- Update multiple fields at once
- Authentication support
- More update functions for various data types
- Better support for floats

## How to use:

Create a database object with some info about your database!

~~~c
const char * host = "192.168.1.152";  // ip or domain name
uint16_t port = 8086; // Port your server is listening for data on. Default is 8086

ESP8266InfluxClient influx_server = ESP8266InfluxClient(host, port);
~~~

Create a Measurement struct with the settings for the specific field you want to update.  
If you're logging multiple measurements, create multiple structs with the relevant info for each.
~~~c
Measurement bedroom_temp = {
  "house_iot_data",  // Database name
  "bedroom",   // Measurement name
  "fahrenheit",      // Field key
  "bedroom-esp8266-01", // Host name (A name or unique id for the sensor)
  "us-east"     // Region
};
~~~

Pass that function, and a value, to the update function!
~~~c
influx_server.update(bedroom_temp, read_temp());
~~~

## Example:
See [data_logger.ino](examples/data_logger.ino)
