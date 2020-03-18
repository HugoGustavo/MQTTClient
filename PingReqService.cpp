#include "PingReqService.hpp"

using namespace std;

PingReqService::PingReqService(WiFi* wifi){
    this->wifi = wifi;
}

PingReq* PingReqService::create(){
    return new PingReq();
}

PingReq* PingReqService::read(){
    Bytes* bytes = this->wifi->read();
    PingReq* pingReq = bytes->isEmpty() ? nullptr : new PingReq(bytes);
    return pingReq;
}

void PingReqService::write( PingReq* pingReq){
    if( pingReq == nullptr ) return;
    this->wifi->write(pingReq->toBytes());
}
