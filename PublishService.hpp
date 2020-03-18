#ifndef PUBLISH_SERVICE_HPP
#define PUBLISH_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Publish.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class PublishService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        PublishService(ControlPacketProxy* controlPacketProxy);

        Publish* create();

        Publish* read();
        
        void write( Publish* publish);
};

#endif