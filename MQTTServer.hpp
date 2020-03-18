#ifndef MQTT_SERVER_HPP
#define MQTT_SERVER_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Connect.hpp"
#include "Connack.hpp"
#include "Publish.hpp"
#include "PubRec.hpp"
#include "PubRel.hpp"
#include "PubComp.hpp"
#include "Logger.hpp"

using namespace std;

class MQTTServer {
    private:
        Connect*    connect;
        Connack*    connack;
        Publish*    publish;
        PubRec*     pubRec;
        PubRel*     pubRel;
        PubComp*    pubComp;

    public:
        MQTTServer();

        void request(Bytes* bytes);

        Bytes* response();

    private:
        void reset();
};

#endif