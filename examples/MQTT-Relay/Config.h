#ifndef Config_h
#define Config_h

#define Username "<registered-email>" // https://iot.geekyworks.com
#define MyApiKey "<your-api-key>" // TODO: Change to your Geeky_IoT API Key. Your API Key is displayed on dashboard
#define TopicIdentifier "<controller-id>" // TODO: Change to Controller identifier. Your controller identifier is displayed on dashboard

// WiFi
#define MySSID "<ssid>" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "<password>" // TODO: Change to your Wifi network password

// Relay switch index
#define SWITCH_1  0
#define SWITCH_2  1
#define SWITCH_3  2
#define SWITCH_4  3

const char* mqtt_host = "103.250.184.102"; // Geekyworks MQTT broker ip
const int mqtt_port = 8085;

const char* light1 = "<device-id>"; // Light One
const char* light2 = "<device-id>"; // Light Two
const char* light3 = "<device-id>"; // Light Three
const char* outlet = "<device-id>"; // Plug Two

// Sensor Pins
const int LED_BUILTIN = 2;

#endif
