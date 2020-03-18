#ifndef MQTT_CLIENT_HPP
#define MQTT_CLIENT_HPP

#include "Arduino.h"
#include "ESP8266.h"
#include "WiFi.hpp"
#include "ControlPacketProxy.hpp"
#include "ConnackService.hpp"
#include "ConnectService.hpp"
#include "DisconnectService.hpp"
#include "PingReqService.hpp"
#include "PingRespService.hpp"
#include "PubAckService.hpp"
#include "PubCompService.hpp"
#include "PublishService.hpp"
#include "PubRecService.hpp"
#include "PubRelService.hpp"
#include "MQTTService.hpp"
#include "MQTTServer.hpp"

using namespace std;

class MQTTClient {
    private:
        WiFi*               wifi;
        PingReqService*     pingReqService;
        PingRespService*    pingRespService;
        ControlPacketProxy* controlPacketProxy;
        ConnackService*     connackService;
        ConnectService*     connectService;
        DisconnectService*  disconnectService;
        PubAckService*      pubAckService;
        PubCompService*     pubCompService;
        PublishService*     publishService;
        PubRecService*      pubRecService;
        PubRelService*      pubRelService;
        MQTTService*        mqttService;

    public:
        static const unsigned char QOS_LEVEL_0 = 0x00;
        static const unsigned char QOS_LEVEL_1 = 0x01;
        static const unsigned char QOS_LEVEL_2 = 0x02;

        MQTTClient(ESP8266* esp8266);

        ~MQTTClient();

        void connect(String id, String host, const unsigned int port=1883, const unsigned int keepAlive=60, const bool cleanSession=true);

        void publish(String topic, String payload, const unsigned char qos=MQTTClient::QOS_LEVEL_0, const bool retain=false);

        void disconnect();
};

#endif