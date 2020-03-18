#ifndef PACKET_UTIL_HPP
#define PACKET_UTIL_HPP

#include "Arduino.h"
#include "Bytes.hpp"

using namespace std;

class PacketUtil {
    public:     
        static Bytes* build(String* input);
        static Bytes* build(const uint8_t* buffer, const uint32_t size);
        static String* build(Bytes* bytes, unsigned int from=2);
        static String* build(Bytes* bytes, unsigned int* from);
        static void println(Bytes* input);
        static void print(Bytes* input);
        static void print(const unsigned char input);
        static String* toString(Bytes* input);
};

#endif