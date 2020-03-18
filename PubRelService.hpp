#ifndef PUB_REL_SERVICE_HPP
#define PUB_REL_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Session.hpp"
#include "PubRel.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class PubRelService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        PubRelService(ControlPacketProxy* controlPacketProxy);

        PubRel* create();

        PubRel* read();
        
        void write( PubRel* pubRel);
};

#endif