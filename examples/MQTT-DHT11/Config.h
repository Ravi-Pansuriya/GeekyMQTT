#ifndef Config_h
#define Config_h

#define Username "<registered-email>" // https://iot.geekyworks.com
#define MyApiKey "<your-api-key>" // TODO: Change to your Geeky_IoT API Key. Your API Key is displayed on dashboard
#define TopicIdentifier "<controller-id>" // TODO: Change to Controller identifier. Your controller identifier is displayed on dashboard

// WiFi
#define MySSID "<ssid>" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "<password>" // TODO: Change to your Wifi network password

#define DHT_INTERVAL 60000 // Set Min to 1 Minute (60Sec * 1000)
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const char* mqtt_host = "103.250.184.102"; // Geekyworks MQTT broker ip
const int mqtt_port = 8085;

const char* temperatureId = "<device-id>";  // TODO: Change with temperature sensor identifier
const char* humidityId = "<device-id>"; // TODO: Change with humidity sensor identifier

// Sensor Pins
const int LED_BUILTIN = 2;
const int DHTPin = 32; // Set you DHT pin here

#endif
