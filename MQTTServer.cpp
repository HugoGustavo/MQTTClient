#include "MQTTServer.hpp"

MQTTServer::MQTTServer(){
    this->connect   = nullptr;
    this->connack   = nullptr;
    this->publish   = nullptr;
    this->pubRec    = nullptr;
    this->pubRel    = nullptr;
    this->pubComp   = nullptr;
}

void MQTTServer::request(Bytes* bytes){
    if ( connect == nullptr ){
        this->connect = new Connect(bytes);
    } else if ( publish == nullptr ){
        this->publish = new Publish(bytes);
    } else {
        this->pubRel = new PubRel(bytes);
    }
}

Bytes* MQTTServer::response(){
    if( this->connack == nullptr ){
        this->connack = new Connack(false, Connack::RETURN_CODE_CONNECTION_ACCEPTED);
        return this->connack->toBytes();
    } else if ( this->pubRec == nullptr ){
        this->pubRec = new PubRec(this->publish->getPacketIdentifier());
        return this->pubRec->toBytes();
    } else if ( this->pubComp == nullptr ){
        this->pubComp = new PubComp(this->pubRec->getPacketIdentifier());
        return this->pubComp->toBytes();
    }

    reset();
    return nullptr;
}

void MQTTServer::reset() {
    delete(this->connect);
    delete(this->connack);
    delete(this->publish);
    delete(this->pubRec);
    delete(this->pubRel);
    delete(this->pubComp);

    this->connect   = nullptr;
    this->connack   = nullptr;
    this->publish   = nullptr;
    this->pubRec    = nullptr;
    this->pubRel    = nullptr;
    this->pubComp   = nullptr;
}