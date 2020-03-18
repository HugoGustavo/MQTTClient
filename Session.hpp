#ifndef SESSION_HPP
#define SESSION_HPP

#include "Arduino.h"
#include "Publish.hpp"
#include "PubRec.hpp"
#include "PubRel.hpp"
#include "PubAck.hpp"
#include "Logger.hpp"

using namespace std;

class Session {
    private:
        String*                 id;
        bool                    clean;
        String*                 host;
        unsigned int            port;
        unsigned int            keepAlive;
        unsigned char           qos;
        bool                    retain;
        unsigned long           timeLastPackage;
        bool                    connected;
        String*                 username;
        String*                 password;

        Publish*                unacknowledgedPublish;
        PubRel*                 unacknowledgedPubRel;
        PubRec*                 unacknowledgedPubRec;

        unsigned int            packetIdentifier;
        unsigned int            lastPacketIdentifier;

        static Session*         instance;
        
        Session();
    
    public:
        static const unsigned char QOS_LEVEL_0 = 0x00;
        static const unsigned char QOS_LEVEL_1 = 0x01;
        static const unsigned char QOS_LEVEL_2 = 0x02;
        
        static Session* getInstance();

        String* getId();

        void setId(String* id);

        bool isClean();

        void setClean(const bool clean);

        String* getHost();

        void setHost(String* host);

        unsigned int getPort();

        void setPort(const unsigned int port);

        unsigned int getKeepAlive();

        void setKeepAlive(const unsigned int keepAlive);

        unsigned char getQoS();

        void setQoS(const unsigned char qos);

        bool isRetain();

        void setRetain(const bool retain);

        unsigned long getTimeLastPackage();

        void setTimeLastPackage(const unsigned long timeLastPackage);

        bool isConnected();

        void setConnected(const bool connected);

        String* getUsername();

        void setUsername(String* username);

        String* getPassword();

        void setPassword(String* password);

        void signalTimeLastPackage();

        bool isExpired();

        void setUnacknowledgedPublish(Publish* unacknowledgedPublish);

        void setUnacknowledgedPubRel(PubRel* unacknowledgedPubRel);

        void setUnacknowledgedPubRec(PubRec* unacknowledgedPubRec);

        void confirm(const unsigned int packetIdentifier);

        unsigned int generatePacketIdentifier();

        unsigned int getLastPacketIdentifier();

        void reset();
};

#endif