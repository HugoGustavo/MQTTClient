#include "PubAck.hpp"

using namespace std;

PubAck::PubAck(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::TYPE_PUBACK, ControlPacket::FLAG_PUBACK){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubAck::PubAck(Bytes* bytes) : ControlPacket(bytes){
    unsigned int msbPacketIdentifier = (unsigned int) (bytes->at(2) << 8);
    unsigned int lsbPacketIdentifier = (unsigned int) bytes->at(3);
    this->packetIdentifier = msbPacketIdentifier + lsbPacketIdentifier;
}

PubAck::~PubAck(){

}

unsigned int PubAck::getPacketIdentifier(){
    return packetIdentifier;
}

void PubAck::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubAck::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    
    return result;
}

String* PubAck::toString(){
    return &("PubAck [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +
        ", packetIdentifier=" + String(this->packetIdentifier) + "]");
}
