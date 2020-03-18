#include "PingResp.hpp"

using namespace std;

PingResp::PingResp() : ControlPacket(ControlPacket::TYPE_PINGRESP, ControlPacket::FLAG_PINGRESP){
    this->remainingLength = 0x00;
}

PingResp::PingResp(Bytes* bytes) : ControlPacket(bytes){

}

PingResp::~PingResp(){

}

Bytes* PingResp::toBytes(){
    return ControlPacket::toBytes();
}

String* PingResp::toString(){
    return &("PingResp [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +"]");
}
