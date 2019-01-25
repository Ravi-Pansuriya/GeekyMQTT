#include "GeekyMQTT.h"
#include <WiFi.h>

GeekyMQTT::GeekyMQTT(Client& client, String username, String password){
  _client.setClient(client);
  _username = username;
  _password = password;
}

void GeekyMQTT::setServer(const char* mqttHost, int port){
  _client.setServer(mqttHost, port);
}

String GeekyMQTT::clientId(){
  return _clientId;
}

// Generate client id based on MAC address and last 8 bits of microsecond counter
String GeekyMQTT::generateClientId(boolean isPublish){
  String _id = "ESP32-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  _id += GeekyMQTT::macToStr(mac);
  _id += (isPublish ? "-pub" : "-sub");
  _id += String(micros() & 0xff, 16);
  return _id;
}

// Static functions
String GeekyMQTT::macToStr(const uint8_t* mac){
    String result;
    for (int i = 0; i < 6; ++i) {
        result += String(mac[i], 16);
    //    if (i < 5)
    //      result += ':';
    }
    return result;
}

/* Private/Protected methods*/
boolean GeekyMQTT::connect() {
  byte _connectionCounter = 0;
  /* Loop till 3 tries */
  while (!_client.connected() && _connectionCounter < 3) {
    /* connect now */
    if (_client.connect(_clientId.c_str(), _username.c_str(), _password.c_str())) {
      Serial.print("Connected as: ");
      Serial.println(_clientId);
      return true;
    } else {
      _connectionCounter += 1;
    }
    delay(50);
  }
  return false;
}
