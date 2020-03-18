#ifndef CONTROL_PACKET_PROXY
#define CONTROL_PACKET_PROXY

#include "Arduino.h"
#include "Bytes.hpp"
#include "WiFi.hpp"
#include "Logger.hpp"
#include "Session.hpp"
#include "PacketUtil.hpp"
#include "PingReqService.hpp"
#include "PingRespService.hpp"

using namespace std;

class ControlPacketProxy {
    private:
        WiFi*               wifi;
        PingReqService*     pingReqService;
        PingRespService*    pingRespService;
        unsigned int        connectionAttempts;

    public:
        ControlPacketProxy(WiFi* wifi, PingReqService* pingReqService, PingRespService* pingRespService, const unsigned int connectionAttempts=10);

        void connect(String* ip, const unsigned int port);

        void disconnect();

        bool isConnected();

        Bytes* read();

        void write(Bytes* bytes);
};

#endif