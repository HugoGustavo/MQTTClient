#include "PingRespService.hpp"

using namespace std;

PingRespService::PingRespService(WiFi* wifi){
    this->wifi = wifi;
}

PingResp* PingRespService::create(){
    return new PingResp();
}

PingResp* PingRespService::read(){
    Bytes* bytes = this->wifi->read();
    PingResp* pingResp = bytes->isEmpty() ? nullptr : new PingResp(bytes);
    return pingResp;
}

void PingRespService::write(PingResp* pingResp){
    if( pingResp == nullptr ) return;
    this->wifi->write(pingResp->toBytes());
}
