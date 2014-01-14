#ifndef __KO__JsonUtil__
#define __KO__JsonUtil__

#include <iostream>

#include "cocos2d.h"

#include "json/json.h"

class JsonUtil : public cocos2d::Object {
    
    
public:
    JsonUtil();
    ~JsonUtil();
    
    /// Return JSON representation of an array  or dictionary or object
    static std::string jsonStringWithObject(Object* object);
    static std::string jsonStringWithArray(cocos2d::Array* array);
    static std::string jsonStringWithDictionary(cocos2d::Dictionary* dictionary);
    
    static Json::Value jsonValueWithObject(cocos2d::Object* object);
    static Json::Value jsonValueWithArray(cocos2d::Array* array);
    static Json::Value jsonValueWithDictionary(cocos2d::Dictionary* dictionary);
    
    static cocos2d::Object* objectWithString(const std::string& jsonString);
    
    static cocos2d::Object* objectWithJsonValue( Json::Value value );
};

#endif
