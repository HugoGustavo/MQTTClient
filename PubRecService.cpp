#include "PubRecService.hpp"

using namespace std;

PubRecService::PubRecService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

PubRec* PubRecService::create(){
    Session* session = Session::getInstance();
    unsigned int packetIdentifier = session->getLastPacketIdentifier();
    return new PubRec(packetIdentifier);
}

PubRec* PubRecService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    PubRec* pubRec = bytes->isEmpty() ? nullptr : new PubRec(bytes);
    return pubRec;
}
        
void PubRecService::write( PubRec* pubRec){
    if ( pubRec == nullptr ) return;
    this->controlPacketProxy->write(pubRec->toBytes());
}
