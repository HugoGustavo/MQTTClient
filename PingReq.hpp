#ifndef PING_REQ_HPP
#define PING_REQ_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PingReq : public ControlPacket {
    public:
        PingReq();

        PingReq(Bytes* bytes);

        ~PingReq();

        Bytes* toBytes();

        String* toString();
};

#endif