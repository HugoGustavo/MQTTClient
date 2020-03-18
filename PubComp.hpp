#ifndef PUB_COMP_HPP
#define PUB_COMP_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubComp : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubComp(const unsigned int packetIdentifier);

        PubComp(Bytes* bytes);

        ~PubComp();

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        Bytes* toBytes();

        String* toString();
};

#endif