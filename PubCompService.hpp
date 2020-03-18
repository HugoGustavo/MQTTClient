#ifndef PUB_COMP_SERVICE_HPP
#define PUB_COMP_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PubComp.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class PubCompService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        PubCompService(ControlPacketProxy* controlPacketProxy);

        PubComp* create();

        PubComp* read();
        
        void write( PubComp* pubComp);
};

#endif