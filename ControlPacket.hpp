#ifndef CONTROL_PACKET_HPP
#define CONTROL_PACKET_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"

using namespace std;

class ControlPacket {
    protected:
        unsigned char   type;
        unsigned char   flags;
        long int        remainingLength;

    public:
        static const unsigned char TYPE_CONNECT      = 0x10;
        static const unsigned char TYPE_CONNACK      = 0x20;
        static const unsigned char TYPE_PUBLISH      = 0x30;
        static const unsigned char TYPE_PUBACK       = 0x40;
        static const unsigned char TYPE_PUBREC       = 0x50;
        static const unsigned char TYPE_PUBREL       = 0x60;
        static const unsigned char TYPE_PUBCOMP      = 0x70;
        static const unsigned char TYPE_SUBSCRIBE    = 0x80;
        static const unsigned char TYPE_SUBACK       = 0x90;
        static const unsigned char TYPE_UNSUBSCRIBE  = 0xA0;
        static const unsigned char TYPE_UNSUBACK     = 0xB0;
        static const unsigned char TYPE_PINGREQ      = 0xC0;
        static const unsigned char TYPE_PINGRESP     = 0xD0;
        static const unsigned char TYPE_DISCONNECT   = 0xE0;

        static const unsigned char FLAG_CONNECT      = 0x00;
        static const unsigned char FLAG_CONNACK      = 0x00;
        static const unsigned char FLAG_PUBLISH      = 0x00;
        static const unsigned char FLAG_PUBACK       = 0x00;
        static const unsigned char FLAG_PUBREC       = 0x00;
        static const unsigned char FLAG_PUBREL       = 0x02;
        static const unsigned char FLAG_PUBCOMP      = 0x00;
        static const unsigned char FLAG_SUBSCRIBE    = 0x02;
        static const unsigned char FLAG_SUBACK       = 0x00;
        static const unsigned char FLAG_UNSUBSCRIBE  = 0x02;
        static const unsigned char FLAG_UNSUBACK     = 0x00;
        static const unsigned char FLAG_PINGREQ      = 0x00;
        static const unsigned char FLAG_PINGRESP     = 0x00;
        static const unsigned char FLAG_DISCONNECT   = 0x00;

    public:
        ControlPacket(const unsigned char type, const unsigned char flags, const long int remainingLength=0x00000000);

        ControlPacket(Bytes* bytes);

        ~ControlPacket();

        unsigned char getType();
        
        void setType(const unsigned char type);
        
        unsigned char getFlags();
    
        void setFlags(const unsigned char flags);

        long int getRemainingLength();

        void setRemainingLength(const long int remainingLength);

        Bytes* toBytes();

        String* toString();

};

#endif
