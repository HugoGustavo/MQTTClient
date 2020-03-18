#include "StringUtil.hpp"

using namespace std;

bool StringUtil::isEmpty(String* string){
    if ( string == nullptr ) return true;
    String* copy = new String(string->c_str()); copy->trim();
    return copy->length() <= 0;
}

String* StringUtil::getNullAsEmpty(String* string){
    if ( StringUtil::isEmpty(string) ) return new String();
    return string;
}

String* StringUtil::getEmptyAsNull(String* string){
    if ( StringUtil::isEmpty(string) ) return nullptr;
    return string;
}