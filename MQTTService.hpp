#ifndef MQTT_SERVICE_HPP
#define MQTT_SERVICE_HPP

#include "Arduino.h"
#include "ESP8266.h"
#include "Bytes.hpp"
#include "Session.hpp"
#include "ConnackService.hpp"
#include "ConnectService.hpp"
#include "DisconnectService.hpp"
#include "PubAckService.hpp"
#include "PubCompService.hpp"
#include "PublishService.hpp"
#include "PubRecService.hpp"
#include "PubRelService.hpp"
#include "StringUtil.hpp"
#include "Logger.hpp"

using namespace std;

class MQTTService {
    private:
        ControlPacketProxy* controlPacketProxy;
        ConnackService*     connackService;
        ConnectService*     connectService;
        DisconnectService*  disconnectService;
        PubAckService*      pubAckService;
        PubCompService*     pubCompService;
        PublishService*     publishService;
        PubRecService*      pubRecService;
        PubRelService*      pubRelService;

    public:
        static const unsigned char QOS_LEVEL_0 = 0x00;
        static const unsigned char QOS_LEVEL_1 = 0x01;
        static const unsigned char QOS_LEVEL_2 = 0x02;
        
        MQTTService(ControlPacketProxy* controlPacketProxy, ConnackService* connackService, ConnectService* connectService, DisconnectService* disconnectService, PubAckService* pubAckService, PubCompService* pubCompService, PublishService* publishService, PubRecService* pubRecService, PubRelService* pubRelService);

        void connect(String* id, String* host, const unsigned int port=1883, const unsigned int keepAlive=60, const bool cleanSession=true);

        void publish(String* topic, String* payload, const unsigned char qos=MQTTService::QOS_LEVEL_0, const bool retain=false);

        void disconnect();
};

#endif