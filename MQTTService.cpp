#include "MQTTService.hpp"

using namespace std;

MQTTService::MQTTService(ControlPacketProxy* controlPacketProxy, ConnackService* connackService, ConnectService* connectService, DisconnectService* disconnectService, PubAckService* pubAckService, PubCompService* pubCompService, PublishService* publishService, PubRecService* pubRecService, PubRelService* pubRelService){
    this->controlPacketProxy    = controlPacketProxy;
    this->connackService        = connackService;
    this->connectService        = connectService;
    this->disconnectService     = disconnectService;
    this->pubAckService         = pubAckService;
    this->pubCompService        = pubCompService;
    this->publishService        = publishService;
    this->pubRecService         = pubRecService;
    this->pubRelService         = pubRelService;
}

void MQTTService::connect(String* id, String* host, const unsigned int port, const unsigned int keepAlive, const bool cleanSession){
    Session* session = Session::getInstance();
    session->setId(id);
    session->setHost(host);
    session->setPort(port);
    session->setKeepAlive(keepAlive);
    session->setClean(cleanSession);

    Connect* connect = this->connectService->create();
    this->connectService->write(connect);
    Connack* connack = this->connackService->create();
    
    session->setConnected( session->isConnected() && connack->isConnectionAccepted() );

    delete(connack);
    delete(connect);
    connack = nullptr;
    connect = nullptr;
}

void MQTTService::publish(String* topic, String* payload, const unsigned char qos, const bool retain){
    Session* session = Session::getInstance();
    session->setQoS(qos);
    session->setRetain(retain);

    if( session->isConnected() ){
        Publish* publish = this->publishService->create();
        publish->setPayload(payload);
        publish->setTopicName(topic);
        this->publishService->write(publish);

        if ( session->getQoS() == Publish::QOS_LEVEL_1 ){
            session->setUnacknowledgedPublish(publish);
            PubAck* pubAck = this->pubAckService->create();
            session->confirm(pubAck->getPacketIdentifier());
            
            delete(pubAck);
            pubAck = nullptr;
        } else if ( session->getQoS() == Publish::QOS_LEVEL_2 ){
            session->setUnacknowledgedPublish(publish);
            
            PubRec* pubRec = this->pubRecService->create();
            session->confirm(pubRec->getPacketIdentifier());
            session->setUnacknowledgedPubRec(pubRec);

            PubRel* pubRel = this->pubRelService->create();
            this->pubRelService->write(pubRel);
            
            PubComp* pubComp = this->pubCompService->create();
            session->confirm(pubComp->getPacketIdentifier());

            delete(pubComp);
            delete(pubRel);
            delete(pubRec);
            pubComp = nullptr;
            pubRel = nullptr;
            pubRec = nullptr;
        }

        delete(publish);
        publish = nullptr;
    }

}

void MQTTService::disconnect(){
    Disconnect* disconnect = this->disconnectService->create();
    disconnectService->write(disconnect);
    
    delete(disconnect);
    disconnect = nullptr;
}