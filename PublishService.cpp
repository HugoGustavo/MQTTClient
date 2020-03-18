#include "PublishService.hpp"

using namespace std;

PublishService::PublishService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

Publish* PublishService::create(){
    bool            dup         = false;
    Session*        session     = Session::getInstance();
    unsigned char   qos         = session->getQoS();
    bool            retain      = session->isRetain();

    Publish* publish = nullptr;
    switch( qos ){
        case Publish::QOS_LEVEL_0: 
            publish = new Publish(dup, Publish::QOS_LEVEL_0, retain);
            break;
        case Publish::QOS_LEVEL_1: 
            publish = new Publish(dup, Publish::QOS_LEVEL_1, retain); 
            publish->setPacketIdentifier(session->generatePacketIdentifier());
            break;
        case Publish::QOS_LEVEL_2: 
            publish = new Publish(dup, Publish::QOS_LEVEL_2, retain); 
            publish->setPacketIdentifier(session->generatePacketIdentifier());
            break;
        default: 
            publish = new Publish(dup, Publish::QOS_LEVEL_0, retain); 
            break;
    }

    return publish;
}

Publish* PublishService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    Publish* publish = bytes->isEmpty() ? nullptr : new Publish(bytes);
    return publish;
}
        
void PublishService::write( Publish* publish){
    if ( publish == nullptr ) return;
    this->controlPacketProxy->write(publish->toBytes());
}
