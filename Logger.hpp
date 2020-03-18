#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Arduino.h"

using namespace std;

class Logger {
    public:     
        static void trace(String* input);
        static void off(String* input);
        static void fatal(String* input);
        static void error(String* input);
        static void warn(String* input);
        static void info(String* input);
        static void debug(String* input);

        static void trace(const char* input);
        static void off(const char* input);
        static void fatal(const char* input);
        static void error(const char* input);
        static void warn(const char* input);
        static void info(const char* input);
        static void debug(const char* input);
};

#endif