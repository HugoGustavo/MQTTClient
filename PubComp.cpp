#include "PubComp.hpp"

using namespace std;

PubComp::PubComp(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::TYPE_PUBCOMP, ControlPacket::FLAG_PUBCOMP){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubComp::PubComp(Bytes* bytes) : ControlPacket(bytes){
    unsigned int msbPacketIdentifier = (unsigned int) (bytes->at(2) << 8);
    unsigned int lsbPacketIdentifier = (unsigned int) bytes->at(3);
    this->packetIdentifier = msbPacketIdentifier + lsbPacketIdentifier;
}

PubComp::~PubComp(){

}

unsigned int PubComp::getPacketIdentifier(){
    return packetIdentifier;
}

void PubComp::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubComp::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ((0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) (0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    return result;
}

String* PubComp::toString(){
    return &("PubComp [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +
        ", packetIdentifier=" + String(this->packetIdentifier) + "]");
}
