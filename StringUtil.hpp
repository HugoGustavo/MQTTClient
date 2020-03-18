#ifndef STRING_UTIL
#define STRING_UTIL

#include "Arduino.h"

using namespace std;

class StringUtil {
    public:
        static bool isEmpty(String* string);
        static String* getNullAsEmpty(String* string);
        static String* getEmptyAsNull(String* string);
};

#endif