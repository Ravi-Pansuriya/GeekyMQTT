# GeekyMQTT Client

This library provides a client for doing simple publish/subscribe messaging with
geekyworks' iot server that supports MQTT.

## Dependency

This library has dependency of `PubSubClient`. you must first resolve that by installing `PubSubClient` library in you Arduino IDE. [library](https://github.com/knolleary/pubsubclient)

## Examples

The library comes with a number of example sketches. See File > Examples > GeekyMQTT
within the Arduino application.

## Usage

- TODO (Check examples for now)

## Limitations

 - It only works over geekyworks' specified MQTT format and has all the limitation of `PubSubClient`. [library](https://github.com/knolleary/pubsubclient/issues)

## Compatible Hardware

The library is only tested on ESP32 wifi boards. It may work on ESP8266 as well.

## Thanks to

- Nicholas O'Leary (Author of [PubSubClient](https://github.com/knolleary/pubsubclient))

## License

This code is released under the MIT License.
