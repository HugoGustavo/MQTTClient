
#ifndef CONNECT_HPP
#define CONNECT_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class Connect : public ControlPacket {
    private:
        Bytes*          variableHeader;
        unsigned int    keepAlive;
        String*         clientIdentifier;
        String*         willTopic;
        String*         willMessage;
        String*         username;
        String*         password;

    public:
        static const unsigned char QOS_LEVEL_0 = 0x00;
        static const unsigned char QOS_LEVEL_1 = 0x01;
        static const unsigned char QOS_LEVEL_2 = 0x02;

        Connect(const bool username, const bool password, const bool willRetain, const unsigned char willQoS, const bool willFlag, const bool cleanSession, const unsigned int keepAlive=60);

        Connect(Bytes* bytes);

        ~Connect();

        Bytes* getVariableHeader();

        void setVariableHeader(Bytes* variableHeader);

        unsigned int getKeepAlive();

        void setKeepAlive(const unsigned int keepAlive);

        String* getClientIdentifier();

        void setClientIdentifier(String* clientIdentifier);

        String* getWillTopic();

        void setWillTopic(String* willTopic);

        String* getWillMessage();

        void setWillMessage(String* willMessage);

        String* getUsername();

        void setUsername(String* username);

        String* getPassword();

        void setPassword(String* password);

        Bytes* toBytes();

        String* toString();
};

#endif