#include "Logger.hpp"

using namespace std;

void Logger::trace(String* input){
    Serial.println("[TRACE] " + *input);
}

void Logger::off(String* input){
    Serial.println("[OFF] " + *input);
}

void Logger::fatal(String* input){
    Serial.println("[FATAL] " + *input);
}

void Logger::error(String* input){
    Serial.println("[ERROR] " + *input);
}

void Logger::warn(String* input){
    Serial.println("[WARN] " + *input);
}

void Logger::info(String* input){
    Serial.println("[INFO] " + *input);
}

void Logger::debug(String* input){
    Serial.println("[DEBUG] " + *input);
}

void Logger::trace(const char* input){
    Serial.println("[TRACE] " + String(input));
}

void Logger::off(const char* input){
    Serial.println("[OFF] " + String(input));
}

void Logger::fatal(const char* input){
    Serial.println("[FATAL] " + String(input));
}

void Logger::error(const char* input){
    Serial.println("[ERROR] " + String(input));
}

void Logger::warn(const char* input){
    Serial.println("[wARN] " + String(input));
}

void Logger::info(const char* input){
    Serial.println("[INFO] " + String(input));
}

void Logger::debug(const char* input){
    Serial.println("[DEBUG] " + String(input));
}
