#include "Connect.hpp"

using namespace std;

Connect::Connect(const bool username, const bool password, const bool willRetain, const unsigned char willQoS, const bool willFlag, const bool cleanSession, const unsigned int keepAlive) : ControlPacket(ControlPacket::TYPE_CONNECT, ControlPacket::FLAG_CONNECT){
    this->variableHeader = new Bytes();
    this->variableHeader->push_back( (unsigned char) 0 );
    this->variableHeader->push_back( (unsigned char) 4 );
    this->variableHeader->push_back( (unsigned char) 'M' );
    this->variableHeader->push_back( (unsigned char) 'Q' );
    this->variableHeader->push_back( (unsigned char) 'T' );
    this->variableHeader->push_back( (unsigned char) 'T' );
    this->variableHeader->push_back( (unsigned char) 4 );

    // Connect Flag bits  
    unsigned char flags = (unsigned char) 0;  
    flags = flags | ( (username ? 0x01 : 0x00) << 7 ); // User Name Flag
    flags = flags | ( (password ? 0x01 : 0x00) << 6 ); // Password Flag
    flags = flags | ( (willRetain ? 0x01 : 0x00) << 5 ); // Will Retain
    flags = flags | ( (willQoS & 0x03) << 3 ); // Will QoS
    flags = flags | ( (willFlag ? 0x01 : 0x00) << 2 ); // Will Flag
    flags = flags | ( (cleanSession ? 0x01 : 0x00) << 1 ); // Clean Session


    // Condition of willFlag
    if ( ! willFlag ){
        flags = flags | ( 0x00 << 5 ); // Will Retain
        flags = flags | ( 0x00 << 3 ); // Will QoS
    }
    if ( ! username ){
        flags = flags | ( 0x00 << 6 ); // Password Flag
    }

    this->variableHeader->push_back(flags);
    this->keepAlive = keepAlive;
}

Connect::Connect(Bytes* bytes) : ControlPacket(bytes){
    unsigned int index = 2;

    // Protocol Name
    this->variableHeader = new Bytes();
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );

    // Protocol Level
    this->variableHeader->push_back( (unsigned char) bytes->at(index++) );

    // Flags
    this->variableHeader->push_back((unsigned char) bytes->at(index++));

    // Keep Alive
    unsigned int msbKeepAlive = (unsigned int) (bytes->at(index++) << 8);
    unsigned int lsbKeepAlive = (unsigned int) bytes->at(index++);
    this->keepAlive = msbKeepAlive + lsbKeepAlive;

    // Client Identifier
    this->clientIdentifier = PacketUtil::build(bytes, &index);

    // Flags
    unsigned char flags = this->variableHeader->at(7);
    if ( flags & ( 0x01 << 2 ) )
        this->willTopic = PacketUtil::build(bytes, &index);

    if ( flags & ( 0x01 << 2 ) )
        this->willMessage = PacketUtil::build(bytes, &index);

    if ( flags & ( 0x01 << 7 ) ){
        this->username = PacketUtil::build(bytes, &index);
        if ( flags & ( 0x01 << 6 ) )
            this->password = PacketUtil::build(bytes, &index);
    }

}

Connect::~Connect(){
    delete(this->variableHeader);
    this->variableHeader = nullptr;
}

Bytes* Connect::getVariableHeader(){
    return variableHeader;
}

void Connect::setVariableHeader(Bytes* variableHeader){
    this->variableHeader = variableHeader;
}

unsigned int Connect::getKeepAlive(){
    return keepAlive;
}

void Connect::setKeepAlive(const unsigned int keepAlive){
    this->keepAlive = keepAlive;
}

String* Connect::getClientIdentifier(){
    return clientIdentifier;
}

void Connect::setClientIdentifier(String* clientIdentifier){
    this->clientIdentifier = clientIdentifier;
}

String* Connect::getWillTopic(){
    return willTopic;
}

void Connect::setWillTopic(String* willTopic){
    this->willTopic = willTopic;
}

String* Connect::getWillMessage(){
    return willMessage;
}

void Connect::setWillMessage(String* willMessage){
    this->willMessage = willMessage;
}

String* Connect::getUsername(){
    return username;
}

void Connect::setUsername(String* username){
    this->username = username;
}

String* Connect::getPassword(){
    return password;
}

void Connect::setPassword(String* password){
    this->password = password;
}

Bytes* Connect::toBytes(){
    Bytes* payload = new Bytes();

    if ( this->clientIdentifier != nullptr && this->clientIdentifier->length() != 0 ){
        String clientIdentifierSubString = this->clientIdentifier->substring(0,24);
        Bytes* clientIdentifierBytes = PacketUtil::build(&clientIdentifierSubString); // Deve ter no maximo 23 caracteres
        payload->concat(clientIdentifierBytes);
    }

    unsigned char flags = this->variableHeader->at(7);
    if ( ( flags & ( 0x01 << 2 ) ) && this->willTopic != nullptr && this->willTopic->length() != 0 ){
        Bytes* willTopicBytes = PacketUtil::build(this->willTopic);
        payload->concat(willTopicBytes);
    }

    if ( ( flags & ( 0x01 << 2 ) ) && this->willMessage != nullptr && this->willMessage->length() != 0 ){
        Bytes* willMessageBytes = PacketUtil::build(this->willMessage);
        payload->concat(willMessageBytes);
    }
    
    if ( ( flags & ( 0x01 << 7 ) ) && this->username != nullptr && this->username->length() != 0 ){
        Bytes* usernameBytes = PacketUtil::build(this->username); 
        payload->concat(usernameBytes);
        if ( ( flags & ( 0x01 << 6 ) ) && this->password != nullptr && this->password->length() != 0 ){
            Bytes* passwordBytes = PacketUtil::build(this->password);
            payload->concat(passwordBytes);
        }
    }

    this->setRemainingLength( (long int) ( this->variableHeader->getSize() + payload->getSize() + sizeof(this->keepAlive)) );
    
    Bytes* result = ControlPacket::toBytes();
    result->concat(this->variableHeader);
    result->push_back( (unsigned char) ( (this->keepAlive & 0xFF00) >> 8) );
    result->push_back( (unsigned char) ( (this->keepAlive & 0x00FF) ) );
    result->concat(payload);
    return result;
}

String* Connect::toString(){
    return &("Connect [type=" + String(this->type) + 
       ", flags=" + String(this->flags) + 
       ", remainingLength=" + String(this->remainingLength) + 
       ", variableHeader=" + *this->variableHeader->toString() + 
       ", keepAlive=" + String(this->keepAlive) +
       ", clientIdentifier=" + *this->clientIdentifier +
       ", willTopic=" + *this->willTopic +
       ", willMessage=" + *this->willMessage +
       ", username=" + *this->username +
       ", password=" + *this->password + "]");
}
