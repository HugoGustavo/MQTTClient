#include "WiFi.hpp"

using namespace std;

WiFi::WiFi(MQTTServer* mqttServer){
    this->connected     = true;
    this->mqttServer    = mqttServer;
    this->timeout       = 0;
    this->esp8266       = nullptr;
    this->received      = nullptr;
}

WiFi::WiFi(ESP8266* esp8266, const unsigned int timeout){
    this->connected     = false;
    this->esp8266       = esp8266;
    this->timeout       = timeout;
    this->received      = nullptr;
    this->mqttServer    = nullptr;
}

void WiFi::connect(String* ip, const unsigned int port){
    if ( mqttServer != nullptr ){
        this->connected = true;
        return;
    }

    this->connected = this->esp8266->createTCP(*ip, port);
}

void WiFi::disconnect(){
    if ( mqttServer != nullptr ) {
        this->connected = false;
        return;
    }

    this->esp8266->releaseTCP();
    this->connected = false;
}

bool WiFi::isConnected(){
    return this->connected;
}

Bytes* WiFi::read(){
    if ( mqttServer != nullptr ){
        this->received = mqttServer->response();
        return this->received;
    }

    this->length = this->esp8266->recv(this->buffer, sizeof(this->buffer), this->timeout);
    this->received = this->length > 0 ? new Bytes(buffer, this->length) : new Bytes();
    free(buffer);

    return this->received;
}

void WiFi::write(Bytes* bytes){
    if( ! this->connected || bytes == nullptr || bytes->isEmpty() ) return;

    if( mqttServer != nullptr ){
        mqttServer->request(bytes);
        return;
    }

    this->esp8266->send((uint8_t*) bytes->toArray(), bytes->getSize());
}