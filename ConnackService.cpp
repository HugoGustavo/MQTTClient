#include "ConnackService.hpp"

using namespace std;

ConnackService::ConnackService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

Connack* ConnackService::create(){
    Session* session = Session::getInstance();
    bool cleanSession = session->isClean();
    Connack* connack = new Connack(cleanSession, Connack::RETURN_CODE_CONNECTION_ACCEPTED);
    return connack;
}

Connack* ConnackService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    Connack* connack = bytes->isEmpty() ? nullptr : new Connack(bytes);
    return connack;
}
        
void ConnackService::write(Connack* connack){
    if( connack == nullptr ) return;
    this->controlPacketProxy->write(connack->toBytes());
}
