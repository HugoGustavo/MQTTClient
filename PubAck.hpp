#ifndef PUB_ACK_HPP
#define PUB_ACK_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubAck : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubAck(const unsigned int packetIdentifier);

        PubAck(Bytes* bytes);

        ~PubAck();

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        Bytes* toBytes();

        String* toString();
};

#endif