#include "MQTTSubscriber.h"
#include <StringSplitter.h>

MQTTSubscriber::MQTTSubscriber(Client& client, String username, String password): GeekyMQTT(client, username, password){
  _clientId = generateClientId();
}

boolean MQTTSubscriber::loop(){
  /* if client was disconnected then try to reconnect again */
  if (!_client.connected()) {
    if (connect()) {
        _client.subscribe(_topic.c_str());
    }
  }
  return _client.loop();
}

boolean MQTTSubscriber::subscribe(String topic){
    _topic = topic;
  if (!_client.connected()) {
    connect();
  }
  return _client.subscribe(_topic.c_str());
}

void MQTTSubscriber::setCallback(MQTTCallback callback){
    _callback = callback;
    if (callback) {
        _client.setCallback(std::bind(&MQTTSubscriber::_callbackHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }
}

/* Private methods */
void MQTTSubscriber::_callbackHandler(char* topic, uint8_t* payload, unsigned int length){
    StringSplitter *splitter = new StringSplitter(String(topic), '/', 3);
    if (splitter->getItemCount() == 3 && splitter->getItemAtIndex(1) == "device") {
        if (_callback != NULL){
            _callback(String(topic), splitter->getItemAtIndex(2), payload, length);
        }
    }
}
