#ifndef PUB_REC_SERVICE_HPP
#define PUB_REC_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Session.hpp"
#include "PubRec.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class PubRecService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        PubRecService(ControlPacketProxy* controlPacketProxy);

        PubRec* create();

        PubRec* read();
        
        void write( PubRec* pubRec);
};

#endif