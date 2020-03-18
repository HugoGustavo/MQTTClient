#include "PubRelService.hpp"

using namespace std;

PubRelService::PubRelService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

PubRel* PubRelService::create(){
    Session* session = Session::getInstance();
    unsigned int packetIdentifier = session->getLastPacketIdentifier();
    PubRel* pubRel = new PubRel(packetIdentifier);
    return pubRel;
}

PubRel* PubRelService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    PubRel* pubRel = bytes->isEmpty() ? nullptr : new PubRel(bytes);
    return pubRel;
}
        
void PubRelService::write( PubRel* pubRel){
    if ( pubRel == nullptr ) return;
    this->controlPacketProxy->write(pubRel->toBytes());
}
