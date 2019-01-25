#ifndef MQTTPublisher_h
#define MQTTPublisher_h

#include "GeekyMQTT.h"

class MQTTPublisher: public GeekyMQTT{
public:

  /* Construct */
  MQTTPublisher(Client&, String, String);

  /* Basic Functions */
  boolean publish(String, String);
};

#endif
