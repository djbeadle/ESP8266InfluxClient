# ESP8266InfluxClient

A simple way to log data from your ESP 8266 to an InfluxDB server. Designed for use in the ESP 8266 Core for Arduino enviroment. 

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

~~~
int update(
	char* measurement,
	char* field_key,
	int value
);
~~~

## Example:
See [examples/data_logger.ino](data_logger.ino)
