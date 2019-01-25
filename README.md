# Arduino Client for MQTT

This library provides a client for doing simple publish/subscribe messaging with
geekyworks iot server that supports MQTT.

## Dependency

This library has dependency of `PubSubClient`. you must first resolve that by installing `PubSubClient` library in you Arduino IDE.

## Examples

The library comes with a number of example sketches. See File > Examples > GeekyMQTT
within the Arduino application.

Full API documentation is available here: http://pubsubclient.knolleary.net

## Limitations

 - It can only work over geekyworks implementation format and has all the limitation of `PubSubClient`

## Compatible Hardware

The library is only tested on ESP32 wifi boards. It may work on ESP8266 as well:

 - ESP32
 - ESP8266

## License

This code is released under the MIT License.
