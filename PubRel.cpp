#include "PubRel.hpp"

using namespace std;

PubRel::PubRel(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::TYPE_PUBREL, ControlPacket::FLAG_PUBREL){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubRel::PubRel(Bytes* bytes) : ControlPacket(bytes){
    unsigned int msbPacketIdentifier = (unsigned int) (bytes->at(2) << 8);
    unsigned int lsbPacketIdentifier = (unsigned int) bytes->at(3);
    this->packetIdentifier = msbPacketIdentifier + lsbPacketIdentifier;
}

PubRel::~PubRel(){
    this->packetIdentifier = 0;
}

unsigned int PubRel::getPacketIdentifier(){
    return this->packetIdentifier;
}

void PubRel::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubRel::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    unsigned char msbPacketIdentifier = (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 );
    unsigned char lsbPacketIdentifier = (unsigned char) ( 0x00FF & this->packetIdentifier);
    packetIdentifier->push_back(msbPacketIdentifier);
    packetIdentifier->push_back(lsbPacketIdentifier);

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    return result;
}

String* PubRel::toString(){
    return &("PubRel [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +
        ", packetIdentifier=" + String(this->packetIdentifier) + "]");
}