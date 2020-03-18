#ifndef CONNACK_SERVICE_HPP
#define CONNACK_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Connack.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"
#include "Logger.hpp"

using namespace std;

class ConnackService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        ConnackService(ControlPacketProxy* controlPacketProxy);

        Connack* create();

        Connack* read();
        
        void write( Connack* connack);
};

#endif