//
//  RequestManager.h
//  coclua
//
//  Created by anan on 1/2/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#ifndef __RequestManager__
#define __RequestManager__
#include "cocos2d.h"
#include "NetworkHook.h"
#include "SocketUtil.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

USING_NS_CC;

#define BLOCK() do{
#define BLOCK_END() }while(0);
#define LEAVE() break;

class RequestManager : public Object,NetworkHook{
    //pointer to index of delegate table in lua register table
private:
    int                     delegates[1];
    int                     debug_level;
public:
    ~RequestManager();
    
    static RequestManager* sharedRequestManager();
    static int dispatcher(lua_State*l);
    
    void init();
    
    void sendRequestWithParam(const char* type, Dictionary* param);
    void sendRequestWithParam(const char* type, Dictionary* param,int userData);
    void dispatchRequestDidFinish(const char* type, int resultRef);
    void dispatchRequestDidFail(const char*type,const char*message);
    void socketInitAndConnectServer();
    void socketReceiveFromServer(Object*data);
    void socketHandleState(SocketState state);
    void socketReconnect();
    int  delegate();
    void addDelegate();
    void removeDelegate();
protected:
    void sendRequestWithUrl(const char* type, const char* url,int userData);
    void httpRequestDidCompleted(Object *sender, network::HttpResponse *data);
    void log(int level,const char * pszFormat, ...);
private:
    RequestManager();
};
//init request manager object in lua
int lua_auto_requestmanager(lua_State*l);

#endif
