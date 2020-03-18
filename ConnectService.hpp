#ifndef CONNECT_SERVICE_HPP
#define CONNECT_SERVICE_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "Connect.hpp"
#include "ControlPacketProxy.hpp"
#include "StringUtil.hpp"

using namespace std;

class ConnectService {
    private:
        ControlPacketProxy* controlPacketProxy;
    
    public:
        ConnectService(ControlPacketProxy* controlPacketProxy);

        Connect* create();

        Connect* read();
        
        void write(Connect* connect);
};

#endif