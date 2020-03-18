#ifndef PUB_REL_HPP
#define PUB_REL_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubRel : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubRel(const unsigned int packetIdentifier);

        PubRel(Bytes* bytes);

        ~PubRel();

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        Bytes* toBytes();

        String* toString();
};

#endif