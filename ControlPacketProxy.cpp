#include "ControlPacketProxy.hpp"

using namespace std;

ControlPacketProxy::ControlPacketProxy(WiFi* wifi, PingReqService* pingReqService, PingRespService* pingRespService, const unsigned int connectionAttempts){
    this->wifi                  = wifi;
    this->pingReqService        = pingReqService;
    this->pingRespService       = pingRespService;
    this->connectionAttempts    = connectionAttempts;
}

void ControlPacketProxy::connect(String* host, const unsigned int port){
    this->wifi->connect(host, port);
}

void ControlPacketProxy::disconnect(){
    this->wifi->disconnect();
}

bool ControlPacketProxy::isConnected(){
    return this->wifi->isConnected();
}

Bytes* ControlPacketProxy::read(){
    return this->wifi->read();
}

void ControlPacketProxy::write(Bytes* bytes){
    Session* session = Session::getInstance();
    if( session->isExpired() ){
        PingReq* pingReq = this->pingReqService->create();
        this->pingReqService->write(pingReq);

        PingResp* pingResp = this->pingRespService->read();
        if( pingResp == nullptr ) return;
    }

    this->wifi->write(bytes);
    session->signalTimeLastPackage();
}