#ifndef PING_RESP_HPP
#define PING_RESP_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PingResp : public ControlPacket {
    public:
        PingResp();

        PingResp(Bytes* bytes);

        ~PingResp();

        Bytes* toBytes();

        String* toString();
};

#endif