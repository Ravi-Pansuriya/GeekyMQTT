#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>
#include <StringSplitter.h>
#include <MQTTPublisher.h>
#include "Config.h"

/* Variable declarations */
uint64_t ldrTimestamp = 0;

/* Class object declarations */
WiFiMulti WiFiMulti;
WiFiClient pubClient, subClient;
// Init publisher
MQTTPublisher publisher(pubClient, Username, MyApiKey);

/* function declarations */
void uploadToServer(const char*, int, float);

/* function implementations */
// Wifi event handler
void WiFiEvent(WiFiEvent_t event){
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event) {
    case SYSTEM_EVENT_WIFI_READY: 
      Serial.println("WiFi interface ready");
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case SYSTEM_EVENT_SCAN_DONE:
      Serial.println("Completed scan for access points");
      break;
    case SYSTEM_EVENT_STA_START:
      Serial.println("WiFi client started");
      break;
    case SYSTEM_EVENT_STA_STOP:
      Serial.println("WiFi clients stopped");
      break;
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println("Connected to access point");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected from WiFi access point");
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
      Serial.println("Authentication mode of access point has changed");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("Obtained IP address: ");
      Serial.println(WiFi.localIP());
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    default:
      digitalWrite(LED_BUILTIN, LOW);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  delay(10);
  
  pinMode(LDRPin, INPUT);

  WiFi.onEvent(WiFiEvent);  // Set wifi event to moniter connection status
  WiFiMulti.addAP(MySSID, MyWifiPassword);  // Setup WiFi ssid and password
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  /* configure publisher with IPaddress and port of MQTT Broker */
  publisher.setServer(mqtt_host, mqtt_port);
}

void loop() {
  if(WiFiMulti.run() == WL_CONNECTED) {
    uint64_t now = millis();
    // Fetch DHT values after on specified time interval
    if((now - ldrTimestamp) > LDR_INTERVAL) {
        ldrTimestamp = now;
        int ldrValue = analogRead(LDRPin);   // read the input on analog pin 0
        Serial.printf("Value: %d\n", ldrValue);
        float voltage = ldrValue * (3.3 / 4096.0);   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V)
        float val = (voltage / 3.3) * 100.0;
        Serial.printf("Visibility: %.0f%%\n", val);
        if (!isnan(val)){
          uploadToServer(visibilityId, 103, val);
        }
    }
  }
}

// Prepare json data to upload sensor values to the server
void uploadToServer(const char* _id, int type, float val){
  Serial.println("Publishing...");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = type;
  root["client"] = publisher.clientId();
  JsonObject& data = root.createNestedObject("data");
  data["value"] = val;
  // Prepare payload json string
  String jsonString;
  root.printTo(jsonString);
  Serial.println(jsonString);
  // Generate publish topic
  String topic = String(TopicIdentifier);
  topic += "/sensor/";
  topic += _id;
  if(publisher.publish(topic, jsonString)){
    Serial.println("Published successfully..");
  } else {
    Serial.println("Publish failed!");
  }
}
