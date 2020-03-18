#include "DisconnectService.hpp"

using namespace std;

DisconnectService::DisconnectService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

Disconnect* DisconnectService::create(){
    return new Disconnect();
}

Disconnect* DisconnectService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    Disconnect* disconnect = bytes->isEmpty() ? nullptr : new Disconnect(bytes);
    return disconnect;
}
        
void DisconnectService::write(Disconnect* disconnect){
    if ( disconnect == nullptr ) return;
    this->controlPacketProxy->write(disconnect->toBytes());
    this->controlPacketProxy->disconnect();

    Session* session = Session::getInstance();
    session->reset();
}
