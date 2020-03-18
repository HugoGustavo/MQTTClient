#include "Bytes.hpp"

using namespace std;

Bytes::Node::Node(){
    this->value = (unsigned char) 0;
    this->previous = this->next = nullptr;
}

Bytes::Node::~Node(){
    this->value = (unsigned char) 0;
    this->previous = this->next = nullptr;
}

Bytes::Node::Node(const unsigned char value, Bytes::Node* previous, Bytes::Node* next){
    this->value = value;
    this->previous = previous;
    this->next = next;
}

unsigned char Bytes::Node::getValue(){ 
    return this->value;
}

void Bytes::Node::setValue(const unsigned char value){
    this->value = value;
}

Bytes::Node* Bytes::Node::getPrevious(){
    return this->previous;
}

void Bytes::Node::setPrevious(Bytes::Node* previous){
    this->previous = previous;
}

Bytes::Node* Bytes::Node::getNext(){
    return this->next;
}

void Bytes::Node::setNext(Bytes::Node* next){
    this->next = next;
}

Bytes::Bytes(){
    this->front = this->back = nullptr;
    this->size = 0;
}

Bytes::Bytes(const uint8_t* buffer, const uint32_t size){
    this->front = this->back = nullptr;
    this->size = 0;

    for(uint32_t i = 0; i < size; i++) this->push_back(buffer[i]);
}

Bytes::~Bytes(){
    Bytes::Node* current = this->front;
    while( current != nullptr ){
        Bytes::Node* next = current->getNext();
        delete(current);
        current = next;
    }
    
    this->front = this->back = nullptr;
    this->size = 0;
}

bool Bytes::isEmpty(){
    return this->size == 0;
}

unsigned char Bytes::at(const unsigned int index){
    if ( index >= this->size )
        return (unsigned char) 0;
    
    int position = index;
    Bytes::Node* current = this->front;
    while( position != 0 && current != nullptr) {
        current = current->getNext();
        position--;
    }

    return current == nullptr ? (unsigned char) 0 : current->getValue();
}

unsigned char Bytes::atFront(){
    return this->front == nullptr ? (unsigned char) 0 : this->front->getValue();
}

unsigned char Bytes::atBack(){
    return this->back == nullptr ? (unsigned char) 0 : this->back->getValue();
}

void Bytes::push_back(const unsigned char value){
    Bytes::Node* node = new Node(value, this->back, nullptr);

    if ( this->front == nullptr ){
        this->front = this->back = node;
    } else{
        this->back->setNext(node);
        this->back = node;
    }

    this->size++;
}

void Bytes::pop_back(){
    if ( this->back == nullptr ) return;

    if ( this->front == this->back ){
        delete this->front;
        this->front = this->back = nullptr;
    } else {
        Bytes::Node* temp = this->back->getPrevious();
        this->back->setPrevious(nullptr);
        this->back->setNext(nullptr);
        temp->setNext(nullptr);
        delete this->back;
        this->back = temp;
    }

    this->size--;
}

void Bytes::push_front(const unsigned char value){
    Bytes::Node* node = new Bytes::Node(value, nullptr, this->front);

    if ( this->front == nullptr ){
        this->front = this->back = node;
    } else{
        this->front->setPrevious(node);
        this->front = node;
    }

    this->size++;
}

void Bytes::pop_front(){
    if ( this->front == nullptr ) return;

    if ( this->front == this->back ){
        delete this->front;
        this->front = this->back = nullptr;
    } else {
        Bytes::Node* temp = this->front->getNext();
        this->front->setPrevious(nullptr);
        this->front->setNext(nullptr);
        temp->setPrevious(nullptr);
        delete this->front;
        this->front = temp;
    }

    this->size--;
}

unsigned int Bytes::getSize(){
    return this->size;
}

void Bytes::concat(Bytes* other){
    if ( other == nullptr ) return;

    for(unsigned int i = 0; i < other->getSize(); i++){
        this->push_back( other->at(i) );
    }
}

unsigned char* Bytes::toArray(){
    if( this->size == 0 ) return nullptr;
    unsigned char* result = new unsigned char[this->size];
    for(unsigned int i = 0; i < this->getSize(); i++) result[i] = this->at(i);
    return result;
}

bool Bytes::equals(Bytes* that){
    if ( that == nullptr || that->getSize() != this->getSize() ) return false;

    for(unsigned int i = 0; i < this->getSize(); i++)
        if ( this->at(i) != that->at(i) ) return false;
    
    return true;
}

String* Bytes::toString(){
    String* result = new String();
    for(Bytes::Node* current = this->front; current != nullptr ; current = current->getNext()){
        unsigned char value = current->getValue();
        if( ((char) value) >= 33 && ((char) value) <= 126 ) result->concat(String((char) value));
        else {
            if( ((char) value) < 0x10 ) result->concat("\\x" + String(0) + String(value, HEX));
            else result->concat("\\x" + String(value, HEX));
        }
    }
    return result;
}