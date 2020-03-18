#include "PubRec.hpp"

using namespace std;

PubRec::PubRec(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::TYPE_PUBREC, ControlPacket::FLAG_PUBREC){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubRec::PubRec(Bytes* bytes) : ControlPacket(bytes){
    unsigned int msbPacketIdentifier = (unsigned int) (bytes->at(2) << 8);
    unsigned int lsbPacketIdentifier = (unsigned int) bytes->at(3);
    this->packetIdentifier = msbPacketIdentifier + lsbPacketIdentifier;
}

PubRec::~PubRec(){

}

unsigned int PubRec::getPacketIdentifier(){
    return packetIdentifier;
}

void PubRec::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubRec::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    return result;
}

String* PubRec::toString(){
    return &("PubRec [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +
        ", packetIdentifier=" + String(this->packetIdentifier) + "]");
}
