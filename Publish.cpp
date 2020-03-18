#include "Publish.hpp" 

using namespace std;

Publish::Publish(const bool dup, const unsigned char qosLevel, const bool retain) : ControlPacket(ControlPacket::TYPE_PUBLISH, ControlPacket::FLAG_PUBLISH){
    this->dup               = this->qosLevel == 0x00 ? false : dup;
    this->qosLevel          = qosLevel;
    this->retain            = retain;
    this->topicName         = nullptr;
    this->packetIdentifier  = 0;
    this->payload           = nullptr;
    
    this->flags             = 0x00;
    this->flags             = dup ? this->flags | (0x01 << 3) : this->flags;
    this->flags             = this->flags | ( (this->qosLevel & 0x03) << 1 );
    this->flags             = retain ? this->flags | 0x01 : this->flags; 

}

Publish::Publish(Bytes* bytes) : ControlPacket(bytes) {
    this->dup       = this->flags & 0x08 ? true : false;
    this->qosLevel  = (unsigned char) ( (this->flags & 0x06) >> 1 );
    this->retain    = this->flags & 0x01 ? true : false;
    
    unsigned int index = 2;
    this->topicName = PacketUtil::build(bytes, &index);

    if( this->qosLevel == Publish::QOS_LEVEL_1 || this->qosLevel == Publish::QOS_LEVEL_2 ) {
        unsigned int msbPacketIdentifier = (unsigned int) (bytes->at(index++) << 8);
        unsigned int lsbPacketIdentifier = (unsigned int) bytes->at(index++);
        this->packetIdentifier = msbPacketIdentifier + lsbPacketIdentifier;
    }

    this->payload = PacketUtil::build(bytes, &index);
}


Publish::~Publish(){

}

bool Publish::isDup(){
    return dup;
}

void Publish::setDup(const bool dup){
    this->dup = dup;
}

unsigned char Publish::getQoSLevel(){
    return qosLevel;
}

void Publish::setQoSLevel(const unsigned char qosLevel){
    this->qosLevel = qosLevel;
}

bool Publish::isRetain(){
    return retain;
}

void Publish::setRetain(const bool retain){
    this->retain = retain;
}

String* Publish::getTopicName(){
    return topicName;
}

void Publish::setTopicName(String* topicName){
    this->topicName = topicName;
}

unsigned int Publish::getPacketIdentifier(){
    return packetIdentifier;
}

void Publish::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

String* Publish::getPayload(){
    return payload;
}

void Publish::setPayload(String* payload){
    this->payload = payload;
}

Bytes* Publish::toBytes(){
    Bytes* variableHeader = new Bytes();
    if( this->topicName != nullptr && this->topicName->length() != 0 ){
        Bytes* topicNameField = PacketUtil::build(this->topicName);
        variableHeader->concat(topicNameField);
    }

    if( this->qosLevel == Publish::QOS_LEVEL_1 || this->qosLevel == Publish::QOS_LEVEL_2 ) {
        Bytes* packetIdentifierField = new Bytes();
        unsigned char msbPacketIdentifier = (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 );
        unsigned char lsbPacketIdentifier = (unsigned char) (0x00FF & this->packetIdentifier);
        packetIdentifierField->push_back(msbPacketIdentifier);
        packetIdentifierField->push_back(lsbPacketIdentifier);
        variableHeader->concat(packetIdentifierField);
    }

    Bytes* payload = new Bytes();
    if ( this->payload != nullptr && this->payload->length() != 0 )
        payload->concat(PacketUtil::build(this->payload));
        
    this->setRemainingLength( variableHeader->getSize() + payload->getSize() );

    Bytes* result = ControlPacket::toBytes();
    result->concat(variableHeader);
    result->concat(payload);
    return result;
}

String* Publish::toString(){
    return &("Publish [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +
        ", dup=" + String(this->dup) + 
        ", qosLevel=" + String(this->qosLevel) +
        ", retain=" + String(this->qosLevel) +
        ", topicName=" + *this->topicName +
        ", packetIdentifier=" + String(this->packetIdentifier) +
        ", payload=" + *this->payload + "]");
}
