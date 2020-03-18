#include "PingReq.hpp"

using namespace std;

PingReq::PingReq() : ControlPacket(ControlPacket::TYPE_PINGREQ, ControlPacket::FLAG_PINGREQ){
    this->remainingLength = 0x00;
}

PingReq::PingReq(Bytes* bytes) : ControlPacket(bytes){
    
}

PingReq::~PingReq(){

}

Bytes* PingReq::toBytes(){
    return ControlPacket::toBytes();
}

String* PingReq::toString(){
    return &("PingReq [type=" + String(this->type) + 
        ", flags=" + String(this->flags) +
        ", remainingLength=" + String(this->remainingLength) +"]");
}
