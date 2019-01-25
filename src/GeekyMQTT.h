#ifndef GeekyMQTT_h
#define GeekyMQTT_h

#include <Arduino.h>
#include <Client.h>
#include <PubSubClient.h>

class GeekyMQTT{
    private:
    String _username, _password;

    protected:
    PubSubClient _client;

    boolean connect();
    String _clientId;

    public:
    /* Construct */
    GeekyMQTT(Client&, String, String);

    /* Basic Functions */
    void setServer(const char*, int);

    /* Class Based Functions */
    String clientId();
    String generateClientId(boolean isPublish = false);
    
    /* Class Based Static Functions */
    static String macToStr(const uint8_t*);
};

#endif
