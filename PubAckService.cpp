#include "PubAckService.hpp"

using namespace std;

PubAckService::PubAckService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

PubAck* PubAckService::create(){
    Session* session = Session::getInstance();
    unsigned int packetIdentifier = session->getLastPacketIdentifier();
    PubAck* pubAck = new PubAck(packetIdentifier);
    return pubAck;
}

PubAck* PubAckService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    PubAck* pubAck = bytes->isEmpty() ? nullptr : new PubAck(bytes);
    return pubAck;
}
        
void PubAckService::write( PubAck* pubAck){
    if ( pubAck == nullptr ) return;
    this->controlPacketProxy->write(pubAck->toBytes());
}
