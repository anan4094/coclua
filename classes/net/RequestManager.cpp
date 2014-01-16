//
//  RequestManager.cpp
//  coclua
//
//  Created by anan on 1/2/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#include "RequestManager.h"
#include "JsonUtil.h"
#include "luaUtil.h"
#include "baseUtil.h"
#include "CCLuaEngine.h"
#include <stdio.h>
USING_NS_CC;
using namespace network;

#pragma mark function will register in lua
static int lua_addDelegate(lua_State*l){
    RequestManager::sharedRequestManager()->addDelegate();
    return 0;
}
static int lua_removeDelegate(lua_State*l){
    RequestManager::sharedRequestManager()->removeDelegate();
    return 0;
}
static int lua_delegates(lua_State*l){
    lua_rawgeti(l, LUA_REGISTRYINDEX, RequestManager::sharedRequestManager()->delegate());
    return 1;
}
static int lua_sendRequest(lua_State*l){
    int param_num= lua_gettop(l);
    if (param_num==4) {
        //has user data
        lua_pushvalue(l, -1);
        int r = luaL_ref(l, LUA_REGISTRYINDEX);//OK REF
        int num = lua_gettop(l);
        Dictionary*tmp= dynamic_cast<Dictionary*>(lua2object(l, -2));
        RequestManager::sharedRequestManager()->sendRequestWithParam(lua_tostring(l, -3), tmp,r);
    }else if(param_num==3){
        Dictionary*tmp= dynamic_cast<Dictionary*>(lua2object(l, -1));
        RequestManager::sharedRequestManager()->sendRequestWithParam(lua_tostring(l, -2), tmp);
    }else{
        //the number of parameter is not expect
    }
    return 0;
}
static int lua_sendMessage(lua_State*l){
    int param_num= lua_gettop(l);
    if (param_num>=2) {
        Object*tmp = lua2object(l, 2);
        Json::Value jsonValue = JsonUtil::jsonValueWithObject(tmp);
        Json::FastWriter writer;
        std::string jsonString = writer.write(jsonValue);
        std::string jsonStringEncode = UrlEncode(jsonString);
        RequestManager::sharedRequestManager()->sendMessage(jsonStringEncode.c_str());
    }else{
        //the number of parameter is not expect
    }
    return 0;
}
static int  lua_dispatchRequestDidFinish(lua_State*l){
    if (lua_gettop(l)!=3) {
        return 0;
    }else{
        if (!lua_isstring(l, -2)) {
            return 0;
            if (!(lua_isstring(l, -1)||lua_istable(l, -1))) {
                return 0;
            }
        }
    }
    lua_pushvalue(l, -1);
    int r = luaL_ref(l,LUA_REGISTRYINDEX);//OK REF
    RequestManager::sharedRequestManager()->dispatchRequestDidFinish(lua_tostring(l, -2), r);
    return 0;
}

//register requestmanger's function into lua
/*
 [function] means the function is in c++
 RequestManager = {
    addDelegate      = [lua_addDelegate]                  void:(table)
    removeDelegate   = [lua_removeDelegate]               void:(table)
    delegates        = [lua_delegates]                    int:()
    requestDidFinish = [lua_dispatchRequestDidFinish]     void:(string,table)
    sendRequest      = [lua_sendRequest]                  void:(string,table[,any])
    sendMessage      = [lua_sendMessage]                  void:([string|table|...])
 }
 */
int lua_auto_requestmanager(lua_State*l){
    static const luaL_Reg reqlib [] = {
        {"addDelegate", lua_addDelegate},
        {"removeDelegate", lua_removeDelegate},
        {"delegates", lua_delegates},
        {"requestDidFinish",lua_dispatchRequestDidFinish},
        {"sendRequest",lua_sendRequest},
        {"sendMessage",lua_sendMessage},
        {NULL, NULL}  /* sentinel */
    };
    int i=0;
    lua_getglobal(l, "RequestManager");
    if (!lua_istable(l, -1)) {
        lua_pop(l, 1);
        lua_newtable(l);
    }
    
    while (reqlib[i].name) {
        lua_pushstring(l, reqlib[i].name);
        lua_pushcfunction(l, reqlib[i].func);
        lua_settable(l, -3);
        i++;
    }
    lua_setglobal(l, "RequestManager");
    return 0;
}

RequestManager::RequestManager():debug_level(1){
    delegates[0]=LUA_REFNIL;
}

RequestManager::~RequestManager(){
}

static RequestManager *s_SharedRequestManager = NULL;

RequestManager* RequestManager::sharedRequestManager()
{
    if (!s_SharedRequestManager){
        s_SharedRequestManager = new RequestManager();
        s_SharedRequestManager->init();
    }
    
    return s_SharedRequestManager;
}
int RequestManager::dispatcher(lua_State *l){
    return 0;
}

void RequestManager::init(){
    socketInitAndConnectServer();
}
int RequestManager::delegate(){
    return *delegates;
}

void RequestManager::log(int level,const char*pszFormat, ...){
    if (level>debug_level) {
        return;
    }
    printf("RequestManager:");
    char szBuf[kMaxLogLen+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

void RequestManager::sendRequestWithParam(const char*type, Dictionary* param){
    this->sendRequestWithParam(type, param, LUA_REFNIL);
}

void RequestManager::sendRequestWithParam(const char* type, Dictionary* param,int userData){
    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    CHECK_STACK(L,a)
    lua_getglobal(L, "RequestManager");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
    }else{
        lua_pushstring(L, "obtainHttpUrl");
        lua_gettable(L, -2);
        if (lua_isfunction(L, -1)) {
            lua_pushvalue(L, -2);
            lua_pushstring(L, type);
            object2lua(L, param);
            int code = lua_pcall(L, 3, 1, 0);
            if (lua_type(L, -1)==LUA_TSTRING) {
                if (code) {
                    log(1, "obtain http url error:%s",lua_tostring(L, -1));
                    lua_pop(L, 2);
                }else{
                    const char* tmp = lua_tostring(L, -1);
                    lua_pop(L, 2);
                    this->sendRequestWithUrl(type,tmp,userData);
                    return;
                }
            }else{
                lua_pop(L, 2);
            }
        }else{
            lua_pop(L, 2);
        }
    }
    CHECK_STACK_END(L,a, "obtainHttpUrl")
    static char url[128]={0};
    obtainHttpUrl(type, param, url);
    this->sendRequestWithUrl(type,url,userData);
}

void RequestManager::sendRequestWithUrl(const char* type, const char* url,int userData)
{
    HttpRequest* request = new HttpRequest();
    log(1, "send http request[GET]:%s",url);
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(RequestManager::httpRequestDidCompleted));
    request->setTag(type);
    request->setUserData((void*)userData);
    HttpClient::getInstance()->send(request);
    request->release();
}

void RequestManager::sendMessage(const char *msg){
    log(1, "send message:%s",msg);
    m_pSocketUtil->sendMessage(msg);
}

void RequestManager::httpRequestDidCompleted(Object *sender, network::HttpResponse *data){
    HttpResponse *response = data;
    HttpRequest *request = response->getHttpRequest();
    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    BLOCK()
    const char *type = request->getTag();
    if (!response || !strlen(type)){
        LEAVE()
    }
    log(1,"%s completed", type);
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code=>%d, tag = %s", statusCode, request->getTag());
    log(1,"response code==>%d", statusCode);
    
    if (!response->isSucceed()){
        log(1,"response failed");
        log(1,"error buffer: %s", response->getErrorBuffer());
        std::string temName = response->getErrorBuffer();
        
        if (temName.length() > 0){
            if (!((unsigned)temName[0]&0x80)){
                //you need to translate ascii to chinese
            }
        }
        
        this->dispatchRequestDidFail(type, temName.c_str());
        LEAVE()
    }
    std::vector<char> *buffer = response->getResponseData();
    std::string responseData(buffer->begin(),buffer->end());
    
    log(2,"responseData==>%s",responseData.c_str());
    //translate string to object
    Object*result= JsonUtil::objectWithString(responseData);
    
    //http request will be intercepted by c++
    //you can deal with infomation in next function
    if (hookHttpRequest(type, result)) {
        //return true means c++ will handle all things,else lua will handle ones
        LEAVE()
    }
    char*msg=nullptr;
    hookHttpWarnRequest(type,result,msg);
    if (msg) {
        dispatchRequestDidFail(type, msg);
        LEAVE()
    }
    
    //return 0 means find matched method in lua
    //return 1 means not find matched method in lua,and push default result into the stack
    //negative number reserved for data format error
    if(finishRequestForLua(L,type,result,(int)request->getUserData())>0){
        //call default disposal method
        dispatchRequestDidFinish(type,luaL_ref(L,LUA_REGISTRYINDEX));//OK REF
    }
    BLOCK_END()
    if (((int)request->getUserData())!=LUA_REFNIL) {
        luaL_unref(L, LUA_REGISTRYINDEX, (int)request->getUserData());
    }
}

void RequestManager::addDelegate(){
    lua_State*l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    addElement(l,delegates);
}

void RequestManager::removeDelegate(){
    lua_State*l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    removeElement(l,delegates);
}

void RequestManager::dispatchRequestDidFinish(const char* type, int resultRef){
    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    PUSH_STACK(L)
    DISPATCHER(L,*delegates)
    
    lua_pushstring(L, "requestDidFinishWithResult");
    lua_gettable(L, -2);
    if (lua_isfunction(L, -1)) {
        lua_pushvalue(L, -2);
        lua_pushstring(L, type);
        lua_rawgeti(L, LUA_REGISTRYINDEX, resultRef);
        if(lua_pcall(L, 3, 0, 0)){
            log(1, "%s",lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }else{
        lua_pop(L, 1);
    }
            
    DISPATCHER_(L)
    POP_STACK(L)
    luaL_unref(LuaEngine::getInstance()->getLuaStack()->getLuaState(), LUA_REGISTRYINDEX,resultRef);
}

void RequestManager::dispatchRequestDidFail(const char*type,const char*message){
    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    DISPATCHER(L,*delegates)
    
    lua_pushstring(L, "requestDidFailWithMessage");
    lua_gettable(L, -2);
    if (lua_isfunction(L, -1)) {
        lua_pushvalue(L, -2);
        lua_pushstring(L, type);
        lua_pushstring(L, message);
        if(lua_pcall(L, 3, 0, 0)){
            log(1, "%s",lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }else{
        lua_pop(L, 1);
    }
    
    DISPATCHER_(L)
}

void RequestManager::socketInitAndConnectServer(){
    if(m_pSocketUtil){
        m_pSocketUtil->release();
        m_pSocketUtil = nullptr;
    }
    char ip[64]={0};
    int port=0;
    obtainServerAddress(ip,&port);
    m_pSocketUtil = new SocketUtil(ip,port,this);
    m_pSocketUtil->initAndConnect();
}

void RequestManager::socketReceiveFromServer(Object*data){
    //socket message will be intercepted by c++
    //you can deal with infomation in next function
    if(hookSocketMessage(data)){
        //return true means c++ will handle all things,else lua will handle ones
        return;
    }
    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    //return 0 means find receiveSokectMessage method in lua
    //return 1 means not find receiveSokectMessage method in lua,and push default result into the stack
    //negative number reserved for data format error
    if (receiveSocketForLua(L, data)>0) {
        //call default disposal method
        //RTC means 实时通信
        dispatchRequestDidFinish("RTC",luaL_ref(L,LUA_REGISTRYINDEX));//OK REF
    }
}

void RequestManager::socketHandleState(SocketState state){
    switch (state) {
        case ESOCKET_CONNECT_START:{
            log(1, "socket start connecting!");
        }break;
        case ESOCKET_CONNECT_SUC:{
            log(1, "socket connect succefully!");
            socketConnectFinish();
        }break;
        case ESOCKET_CONNECT_FAIL:{
            log(1, "socket connect failed!");
			socketReconnect();
        }break;
        case ESOCKET_RECEIVE_ERROR:{
            log(1, "socket receive error!");
            socketReceiveError();
        }break;
        case ESOCKET_RECONNECT_FAIL:{
            log(1, "socket reconnect failed!");
            socketReconnectFail();
        }break;
        case ESOCKET_DISCONNECTFROMSERVER:{
            log(1, "socket disconnect server!");
            socketDisconnect();
        }break;
        default:
            break;
    }
}

void RequestManager::socketReconnect(){
    if (m_nSocketConnectNum < 3){
		log(1,"reconnect ===== %d", m_nSocketConnectNum);
		socketInitAndConnectServer();
		++m_nSocketConnectNum;
	}else{
        m_nSocketConnectNum = 0;
        socketHandleState(ESOCKET_RECONNECT_FAIL);
    }
}
