#ifndef PING_REQ_SERVICE_HPP
#define PING_REQ_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "WiFi.hpp"
#include "PingReq.hpp"
#include "StringUtil.hpp"

using namespace std;

class PingReqService {
    private:
        WiFi* wifi;
    
    public:
        PingReqService(WiFi* wifi);

        PingReq* create();

        PingReq* read();

        void write( PingReq* pingReq);
};

#endif