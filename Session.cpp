#include "Session.hpp"

using namespace std;

Session* Session::instance = 0;

Session::Session(){
    this->id                            = nullptr;
    this->clean                         = true;
    this->host                          = nullptr;
    this->port                          = 1883;
    this->keepAlive                     = 60;
    this->qos                           = Session::QOS_LEVEL_0;
    this->retain                        = false;
    this->timeLastPackage               = (unsigned long) ( millis() / 1000 );
    this->connected                     = false;
    this->username                      = nullptr;
    this->password                      = nullptr;

    this->unacknowledgedPublish         = nullptr;
    this->unacknowledgedPubRel          = nullptr;
    this->unacknowledgedPubRec          = nullptr;

    this->packetIdentifier      = 0;
}

Session* Session::getInstance(){
    if( Session::instance == 0 )
        Session::instance = new Session();
    return Session::instance;
}

String* Session::getId(){
    return this->id;
}

void Session::setId(String* id){
    this->id = id;
}

bool Session::isClean(){
    return this->clean;
}

void Session::setClean(const bool clean){
    this->clean = clean;
}

String* Session::getHost(){
    return this->host;
}

void Session::setHost(String* host){
    this->host = host;
}

unsigned int Session::getPort(){
    return this->port;
}

void Session::setPort(const unsigned int port){
    this->port = port;
}

unsigned int Session::getKeepAlive(){
    return this->keepAlive;
}

void Session::setKeepAlive(const unsigned int keepAlive){
    this->keepAlive = keepAlive;
}

unsigned char Session::getQoS(){
    return this->qos;
}

void Session::setQoS(const unsigned char qos){
    this->qos = qos;
}

bool Session::isRetain(){
    return this->retain;
}

void Session::setRetain(const bool retain){
    this->retain = retain;
}

unsigned long Session::getTimeLastPackage(){
    return this->timeLastPackage;
}

void Session::setTimeLastPackage(const unsigned long timeLastPackage){
    this->timeLastPackage = timeLastPackage;
}

bool Session::isConnected(){
    return this->connected;
}

void Session::setConnected(const bool connected){
    this->connected = connected;
}

String* Session::getUsername(){
    return this->username;
}

void Session::setUsername(String* username){
    this->username = username;
}

String* Session::getPassword(){
    return this->password;
}

void Session::setPassword(String* password){
    this->password = password;
}

void Session::signalTimeLastPackage(){
    this->timeLastPackage = (unsigned long) ( millis() / 1000 );
}

bool Session::isExpired(){
    unsigned long now = (unsigned long) ( millis() / 1000 );
    return (now - this->timeLastPackage) > this->keepAlive;
}

void Session::setUnacknowledgedPublish(Publish* unacknowledgedPublish){
    this->unacknowledgedPublish = unacknowledgedPublish;
}

void Session::setUnacknowledgedPubRel(PubRel* unacknowledgedPubRel){
    this->unacknowledgedPubRel = unacknowledgedPubRel;
}

void Session::setUnacknowledgedPubRec(PubRec* unacknowledgedPubRec){
    this->unacknowledgedPubRec = unacknowledgedPubRec;
}

void Session::confirm(const unsigned int packetIdentifier){
    if( this->unacknowledgedPublish != nullptr && this->unacknowledgedPublish->getPacketIdentifier() == packetIdentifier )
        this->unacknowledgedPublish = nullptr;

    if( this->unacknowledgedPubRel != nullptr && this->unacknowledgedPubRel->getPacketIdentifier() == packetIdentifier )
        this->unacknowledgedPubRel = nullptr;

    if( this->unacknowledgedPubRec != nullptr && this->unacknowledgedPubRec->getPacketIdentifier() == packetIdentifier )
        this->unacknowledgedPubRec = nullptr;
}

unsigned int Session::generatePacketIdentifier(){
    unsigned int result = this->packetIdentifier;
    this->packetIdentifier = (this->packetIdentifier + 1) % 65534;
    return result;
}

unsigned int Session::getLastPacketIdentifier(){
    return this->packetIdentifier != 0 ? this->packetIdentifier - 1 : 0;
}

void Session::reset(){
    this->id                            = nullptr;
    this->clean                         = true;
    this->host                          = nullptr;
    this->port                          = 1883;
    this->keepAlive                     = 60;
    this->qos                           = Session::QOS_LEVEL_0;
    this->retain                        = false;
    this->timeLastPackage               = (unsigned long) ( millis() / 1000 );
    this->connected                     = false;
    this->username                      = nullptr;
    this->password                      = nullptr;

    this->unacknowledgedPublish         = nullptr;
    this->unacknowledgedPubRel          = nullptr;
    this->unacknowledgedPubRec          = nullptr;

    this->packetIdentifier              = 0;
}