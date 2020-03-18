#include "Disconnect.hpp"

using namespace std;

Disconnect::Disconnect() : ControlPacket(ControlPacket::TYPE_DISCONNECT, ControlPacket::FLAG_DISCONNECT){
    this->remainingLength = 0x00;
}

Disconnect::Disconnect(Bytes* bytes) : ControlPacket(bytes){
    
}

Disconnect::~Disconnect(){

}

Bytes* Disconnect::toBytes(){
    return ControlPacket::toBytes();
}

String* Disconnect::toString(){
    return &("Disconnect [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +"]");
}
