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
#include "SocketUtil.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

USING_NS_CC;

#define BLOCK() do{
#define BLOCK_END() }while(0);
#define LEAVE() break;


class RequestManagerDelegate{
public:
    virtual void requestDidFailWithMessage(const char* type, const char* errorMessage) = 0;
    virtual void requestDidFinishWithResult(const char* type, void* resultObject)      = 0;
};

typedef std::list< RequestManagerDelegate * > RequestDelegateList;
typedef std::list< RequestManagerDelegate * >::iterator  RequestDelegateIter;

class RequestManager : public Object{
    //pointer to index of delegate table in lua register table
private:
    int                     delegates[1];
    int                     debug_level;
    int                     m_nSocketConnectNum;
    SocketUtil              *m_pSocketUtil;
    lua_State               *m_pl;
    RequestDelegateList     m_list;
public:
    ~RequestManager();
    RequestManager();
    static RequestManager* getInstance();
    static int dispatcher(lua_State*l);
    
    void init();
    void sendRequestWithParam(const char* type, Dictionary* param);
    void sendRequestWithParam(const char* type, Dictionary* param,int userData);
    void sendMessage(const char*msg);
    void dispatchRequestDidFinish(const char* type, Dictionary* result);
    void dispatchRequestDidFinish(const char* type, int resultRef);
    void dispatchRequestDidFail(const char*type,const char*message);
    void socketInitAndConnectServer();
    void socketReceiveFromServer(Object*data);
    void socketHandleState(SocketState state);
    void socketReconnect();
    int  delegate();
    void addDelegate();
    void removeDelegate();
    void addDelegate(RequestManagerDelegate *delegate);
    void removeDelegate(RequestManagerDelegate *delegate);
    void log(int level,const char * pszFormat, ...);
protected:
    void sendRequestWithUrl(const char* type, const char* url,int userData);
    void httpRequestDidCompleted(Object *sender, network::HttpResponse *data);
    
    virtual void obtainHttpUrl(const char *type,Dictionary* param,char*url)         = 0;
    virtual void obtainServerAddress(char*ip,int*port)                              = 0;
    virtual bool hookHttpRequest(const char *type,Object*result)                    = 0;
    virtual void hookHttpWarnRequest(const char *type,Object*result,const char*msg) = 0;
    virtual bool hookSocketMessage(Object*result)                                   = 0;

    virtual void socketConnectFinish()                                              = 0;
    virtual void socketReconnectFail()                                              = 0;
    virtual void socketDisconnect()                                                 = 0;
    virtual void socketReceiveError()                                               = 0;
};
//init request manager object in lua
int lua_auto_requestmanager(lua_State*l);

#endif
