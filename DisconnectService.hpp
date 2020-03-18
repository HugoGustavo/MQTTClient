#ifndef DISCONNECT_SERVICE_HPP
#define DISCONNECT_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Disconnect.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class DisconnectService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        DisconnectService(ControlPacketProxy* controlPacketProxy);

        Disconnect* create();

        Disconnect* read();
        
        void write(Disconnect* disconnect);
};

#endif