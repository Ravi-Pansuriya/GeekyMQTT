#ifndef MQTTSubscriber_h
#define MQTTSubscriber_h

#include "GeekyMQTT.h"
#include <functional>

#ifdef __AVR__
  typedef void (*MQTTCallback)(String, String, uint8_t*, unsigned int);
#else
  typedef std::function<void (String, String, uint8_t*, unsigned int)> MQTTCallback;
#endif

class MQTTSubscriber: public GeekyMQTT{
private:
    MQTTCallback _callback;
    String _topic;
    void _callbackHandler(char*, uint8_t*, unsigned int);
public:

  /* Construct */
  MQTTSubscriber(Client&, String, String);

  /* Basic Functions */
  boolean loop();
  boolean subscribe(String);
  void setCallback(MQTTCallback);
};

#endif