#include "MQTTClient.hpp"

using namespace std;

MQTTClient::MQTTClient(ESP8266* esp8266){ 
    this->wifi                = new WiFi(esp8266);
    this->pingReqService      = new PingReqService(this->wifi);
    this->pingRespService     = new PingRespService(this->wifi);
    this->controlPacketProxy  = new ControlPacketProxy(this->wifi, this->pingReqService, this->pingRespService);
    this->connackService      = new ConnackService(this->controlPacketProxy);
    this->connectService      = new ConnectService(this->controlPacketProxy);
    this->disconnectService   = new DisconnectService(this->controlPacketProxy);
    this->pubAckService       = new PubAckService(this->controlPacketProxy);
    this->pubCompService      = new PubCompService(this->controlPacketProxy);
    this->publishService      = new PublishService(this->controlPacketProxy);
    this->pubRecService       = new PubRecService(this->controlPacketProxy);
    this->pubRelService       = new PubRelService(this->controlPacketProxy);
    this->mqttService         = new MQTTService(this->controlPacketProxy, this->connackService, this->connectService, this->disconnectService, this->pubAckService, this->pubCompService, this->publishService, this->pubRecService, this->pubRelService);
}

MQTTClient::~MQTTClient(){ 
    delete(this->wifi);
    delete(this->pingReqService);
    delete(this->pingRespService);
    delete(this->controlPacketProxy);
    delete(this->connackService);
    delete(this->connectService);
    delete(this->disconnectService);
    delete(this->pubAckService);
    delete(this->pubCompService);
    delete(this->publishService);
    delete(this->pubRecService);
    delete(this->pubRelService);
    delete(this->mqttService);

    this->wifi                = nullptr;
    this->pingReqService      = nullptr;
    this->pingRespService     = nullptr;
    this->controlPacketProxy  = nullptr;
    this->connackService      = nullptr;
    this->connectService      = nullptr;
    this->disconnectService   = nullptr;
    this->pubAckService       = nullptr;
    this->pubCompService      = nullptr;
    this->publishService      = nullptr;
    this->pubRecService       = nullptr;
    this->pubRelService       = nullptr;
    this->mqttService         = nullptr;
}

void MQTTClient::connect(String id, String host, const unsigned int port, const unsigned int keepAlive, const bool cleanSession){
    this->mqttService->connect(&id, &host, port, keepAlive, cleanSession);
}

void MQTTClient::publish(String topic, String payload, const unsigned char qos, const bool retain){
    this->mqttService->publish(&topic, &payload, qos, retain);
}

void MQTTClient::disconnect(){
    this->mqttService->disconnect();
}