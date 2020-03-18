#include "ConnectService.hpp"

using namespace std;

ConnectService::ConnectService(ControlPacketProxy* controlPacketProxy){
    this->controlPacketProxy = controlPacketProxy;
}

Connect* ConnectService::create(){
    Session* session        = Session::getInstance();

    bool hasUsername        = StringUtil::isEmpty(session->getUsername()) ? false : true;
    bool hasPassword        = StringUtil::isEmpty(session->getPassword()) ? false : true;
    bool isIdEmpty          = StringUtil::isEmpty(session->getId());
    bool clean              = isIdEmpty ? true : session->isClean();
    unsigned int keepAlive  = session->getKeepAlive();
    
    Connect* connect = nullptr; 
    switch( session->getQoS() ){
        case Connect::QOS_LEVEL_0: 
            connect = new Connect(hasUsername, hasPassword, false, Connect::QOS_LEVEL_0, false, clean, keepAlive);
            break;
        case Connect::QOS_LEVEL_1: 
            connect = new Connect(hasUsername, hasPassword, false, Connect::QOS_LEVEL_1, false, clean, keepAlive);
            break;
        case Connect::QOS_LEVEL_2: 
            connect = new Connect(hasUsername, hasPassword, false, Connect::QOS_LEVEL_2, false, clean, keepAlive);
            break;
        default: 
            connect = new Connect(hasUsername, hasPassword, false, Connect::QOS_LEVEL_0, false, clean, keepAlive);
            break;
    }

    if ( hasUsername ) connect->setUsername(session->getUsername());
    if ( hasPassword ) connect->setPassword(session->getPassword());
    if ( ! isIdEmpty ) connect->setClientIdentifier(session->getId());

    return connect;
}

Connect* ConnectService::read(){
    Bytes* bytes = this->controlPacketProxy->read();
    Connect* connect = bytes->isEmpty() ? nullptr : new Connect(bytes);
    return connect;
}
        
void ConnectService::write(Connect* connect){
    if ( connect == nullptr ) return;

    Session* session = Session::getInstance();
    if ( ! session->isConnected() ){
        String* host = session->getHost();
        unsigned int port = session->getPort();
        this->controlPacketProxy->connect(host, port);
        bool connected = this->controlPacketProxy->isConnected();
        session->setConnected(connected);
    }
    
    this->controlPacketProxy->write(connect->toBytes());
}
