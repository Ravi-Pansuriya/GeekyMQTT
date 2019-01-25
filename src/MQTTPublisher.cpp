#include "MQTTPublisher.h"


MQTTPublisher::MQTTPublisher(Client& client, String username, String password): GeekyMQTT(client, username, password){
  _clientId = generateClientId(true);
}

boolean MQTTPublisher::publish(String topic, String payload){
  if (!_client.connected()) {
    connect();
  }
  return _client.publish(topic.c_str(), payload.c_str());
}
