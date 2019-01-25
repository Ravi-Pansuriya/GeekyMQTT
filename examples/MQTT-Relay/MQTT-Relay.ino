#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>
//#include <Shifty.h>
#include <StringSplitter.h>
#include <MQTTSubscriber.h>
#include "Config.h"
#include "ShiftySwitches.h"

/* Class object declarations */
WiFiMulti WiFiMulti;
WiFiClient pubClient, subClient;
//MQTTPublisher publisher(pubClient, Username, MyApiKey);
MQTTSubscriber subscriber(subClient, Username, MyApiKey);

/* Default pins for data = 13, clock = 14 and latch = 12 
and by default all the pins set to high to keep relays in off state */
ShiftySwitches switches; 

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

void mqttCallback(String topic, String deviceId, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  
  // Parse payload buffer
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject((char*)payload); 
  String clientId = json["client"];
  boolean value = json["data"]["power"].as<boolean>();
  if(value) {
    if(!switches.turnOn(deviceId)){
      Serial.print("Turn on device id: ");
      Serial.println(deviceId);
    }
  } else {
    if(!switches.turnOff(deviceId)){
      Serial.print("Turn off device id: ");
      Serial.println(deviceId);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  // Add switch ids
  switches.add(light1, 0);
  switches.add(light2, 1);
  switches.add(light3, 2);
  switches.add(outlet, 3);

  WiFi.onEvent(WiFiEvent);
  WiFiMulti.addAP(MySSID, MyWifiPassword);
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

  /* configure subscriber with IPaddress and port of MQTT broker */
  subscriber.setServer(mqtt_host, mqtt_port);
  /* this receivedCallback function will be invoked 
  when client received subscribed topic */
  subscriber.setCallback(mqttCallback);
  // Generate device topic
  String topic = String(TopicIdentifier);
  topic += "/device/#";
  subscriber.subscribe(topic);

}

void loop() {
  if(WiFiMulti.run() == WL_CONNECTED) {  
    /* this function will listen for incomming 
    subscribed topic-process-invoke receivedCallback */
    subscriber.loop();
  }
}
