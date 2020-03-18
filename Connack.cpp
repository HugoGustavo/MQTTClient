#include "Connack.hpp"

using namespace std;

Connack::Connack(const bool cleanSession, const unsigned char returnCode) : ControlPacket(ControlPacket::TYPE_CONNACK, ControlPacket::FLAG_CONNACK) {
    this->cleanSession      = cleanSession;
    this->remainingLength   = 0x02;
    this->returnCode        = returnCode;
}

Connack::Connack(Bytes* bytes) : ControlPacket(bytes){
    this->cleanSession  = bytes->at(2) == 0x00 ? true : false;
    this->returnCode    = bytes->at(3);
}

Connack::~Connack() {

}

bool Connack::isCleanSession(){
    return this->cleanSession;
}

void Connack::setCleanSession(const bool cleanSession){
    this->cleanSession = cleanSession;
}

unsigned char Connack::getReturnCode(){
    return returnCode;
}

void Connack::setReturnCode(const unsigned char returnCode){
    this->returnCode = returnCode;
}

bool Connack::isConnectionAccepted(){
    return this->returnCode == Connack::RETURN_CODE_CONNECTION_ACCEPTED;
}

bool Connack::isRefusedServerUnavailable(){
    return this->returnCode == Connack::RETURN_CODE_CONNECTION_REFUSED_SERVER_UNAVAILABLE;
}

bool Connack::isRefusedBadUsernameOrPassword(){
    return this->returnCode == Connack::RETURN_CODE_CONNECTION_REFUSED_BAD_USERNAME_OR_PASSWORD;
}

bool Connack::isRefusedNotAuthorized(){
    return this->returnCode == Connack::RETURN_CODE_CONNECTION_REFUSED_NOT_AUTHORIZED;
}

Bytes* Connack::toBytes(){
    Bytes* result = ControlPacket::toBytes();
    result->push_back((unsigned char) ( this->cleanSession ? 0x00 : 0x01 ) );
    result->push_back(this->returnCode);
    return result;
}

String* Connack::toString(){
    return &("Connack [type=" + String(this->type) + 
        ", flags=" + String(this->flags) + 
        ", remainingLength=" + String(this->remainingLength) + 
        ", cleanSession=" + String(this->cleanSession) +
        ", returnCode=" + String(this->returnCode) + "]");
}
