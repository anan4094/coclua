//
//  RequestHook.cpp
//  coclua
//
//  Created by anan on 1/6/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#include "CustomRequest.h"
#include "JsonUtil.h"
#include "baseUtil.h"
USING_NS_CC;

void CustomRequest::obtainHttpUrl(const char *type, Dictionary *param, char *url){
    param->setObject(Integer::create(1),"s");
    Json::Value jsonValue = JsonUtil::jsonValueWithDictionary(param);
    Json::FastWriter writer;
    std::string jsonString = writer.write(jsonValue);
    std::string jsonStringEncode = UrlEncode(jsonString);
    sprintf(url, "%s","http://m.weather.com.cn/data/101010100.html");
}
void CustomRequest::obtainServerAddress(char *ip, int *port){
    strcpy(ip, "127.0.0.1");
    *port = 11333;
}
//return true will crash http infomation transfer to lua
bool CustomRequest::hookHttpRequest(const char *type,Object *result){
    return false;
}

//msg is NULL means that there is no warn message when function executed
void CustomRequest::hookHttpWarnRequest(const char *type,Object*result,const char *msg){
    Dictionary*dic = dynamic_cast<Dictionary*>(result);
    if (dic) {
        Integer*err = dynamic_cast<Integer*>(dic->objectForKey("err"));
        String*_msg = dynamic_cast<String*>(dic->objectForKey("msg"));
        if (err && err->getValue() && _msg) {
            msg = _msg->getCString();
        }
    }
    msg = nullptr;
}

//return true will crash socket infomation transfer to lua
bool CustomRequest::hookSocketMessage(Object *result){
    return false;
}

void CustomRequest::socketConnectFinish(){
}

void CustomRequest::socketReconnectFail(){
}

void CustomRequest::socketDisconnect(){
}

void CustomRequest::socketReceiveError(){
}