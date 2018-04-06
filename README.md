# ESP8266InfluxClient

A simple way to log data from your ESP8266 to an InfluxDB server using the [HTTP API](https://docs.influxdata.com/influxdb/v1.5/guides/writing_data/#writing-data-using-the-http-api). Designed for use in the ESP8266 Core for Arduino enviroment. 

Does it work? It seems to! Please open an issue / contribute a pull request if you have fixes, features, optomizations, issues, etc.

#TODO:
- Authentication support
- More update functions for various data types

## Documentation:

Create a database object with some info about your database!

~~~c
ESP8266Influx(
	char* hostname,
	uint16_t port,
	char* database,
	char* tag_region,
	char* tag_host
);
~~~

Send some data to that database!

~~~c
int update(
	char* measurement,
	int value
);
~~~

## Example:
See [data_logger.ino](examples/data_logger.ino)
