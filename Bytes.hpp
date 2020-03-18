#ifndef BYTES_HPP
#define BYTES_HPP

#include "Arduino.h"

using namespace std;

class Bytes {
    private:
        class Node {
            private:
                unsigned char value;
                Node* previous;
                Node* next;

            public:
                Node();

                ~Node();

                Node(const unsigned char value, Node* previous, Node* next);

                unsigned char getValue();
                
                void setValue(const unsigned char value);

                Node* getPrevious();

                void setPrevious(Node* previous);

                Node* getNext();

                void setNext(Node* next);
        };

        Node* front;
        Node* back;
        unsigned int size;

    public:
        Bytes();

        Bytes(const uint8_t* buffer, const uint32_t size);
        
        ~Bytes();

        bool isEmpty();

        unsigned char at(const unsigned int index);
        
        unsigned char atFront();
        
        unsigned char atBack();
        
        void push_back(const unsigned char value);
        
        void pop_back();
        
        void push_front(const unsigned char value);
        
        void pop_front();
        
        unsigned int getSize();
        
        void concat(Bytes* other);
        
        unsigned char* toArray();
        
        bool equals(Bytes* other);

        String* toString();
        
};

#endif