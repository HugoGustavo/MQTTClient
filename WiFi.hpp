#ifndef WIFI_HPP
#define WIFI_HPP

#include <stdlib.h>
#include "Arduino.h"
#include "ESP8266.h"
#include "Bytes.hpp"
#include "Logger.hpp"
#include "PacketUtil.hpp"
#include "MQTTServer.hpp"

using namespace std;

class WiFi {
    private:
        bool            connected;
        ESP8266*        esp8266;
        unsigned int    timeout;
        uint8_t         buffer[4096];
        uint32_t        length;
        Bytes*          received;
        MQTTServer*     mqttServer;
        
    public:
        WiFi(MQTTServer* mqttServer);

        WiFi(ESP8266* esp8266, const unsigned int timeout=10000);

        void connect(String* ip, const unsigned int port);

        void disconnect();

        bool isConnected();

        Bytes* read();

        void write(Bytes* bytes);

};

#endif