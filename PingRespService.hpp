#ifndef PING_RESP_SERVICE_HPP
#define PING_RESP_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "WiFi.hpp"
#include "PingResp.hpp"
#include "StringUtil.hpp"

using namespace std;

class PingRespService {
    private:
        WiFi* wifi;

    public:
        PingRespService(WiFi* wifi);

        PingResp* create();

        PingResp* read();

        void write(PingResp* pingResp);

};

#endif