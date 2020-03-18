#ifndef DISCONNECT_HPP
#define DISCONNECT_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class Disconnect : public ControlPacket {
    public:
        Disconnect();

        Disconnect(Bytes* bytes);

        ~Disconnect();
        
        Bytes* toBytes();

        String* toString();

};

#endif