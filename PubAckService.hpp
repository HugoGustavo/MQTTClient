#ifndef PUB_ACK_SERVICE_HPP
#define PUB_ACK_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PubAck.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class PubAckService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        PubAckService(ControlPacketProxy* controlPacketProxy);

        PubAck* create();

        PubAck* read();
        
        void write( PubAck* pubAck);
};

#endif