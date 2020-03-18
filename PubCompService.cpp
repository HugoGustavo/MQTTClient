#include "PubCompService.hpp"

using namespace std;

PubCompService::PubCompService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

PubComp* PubCompService::create(){
    Session* session = Session::getInstance();
    unsigned int packetIdentifier = session->getLastPacketIdentifier();
    PubComp* pubComp = new PubComp(packetIdentifier);
    return pubComp;
}

PubComp* PubCompService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    PubComp* pubComp = bytes->isEmpty() ? nullptr : new PubComp(bytes);
    return pubComp;
}
        
void PubCompService::write( PubComp* pubComp){
    if ( pubComp == nullptr ) return;
    this->controlPacketProxy->write(pubComp->toBytes());
}
