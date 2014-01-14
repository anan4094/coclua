//
//  RequestHook.h
//  coclua
//
//  Created by anan on 1/6/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#ifndef __NetworkHook__
#define __NetworkHook__

#include "cocos2d.h"
#include "SocketUtil.h"
USING_NS_CC;

class NetworkHook{
public:
    NetworkHook():m_pSocketUtil(NULL),m_nSocketConnectNum(0){}
protected:
    int                     m_nSocketConnectNum;
    SocketUtil              *m_pSocketUtil;
    //need
    void obtainHttpUrl(const char *type,Dictionary* param,char*url);
    void obtainServerAddress(char*ip,int*port);
    bool hookHttpRequest(const char *type,Object*result);
    void hookHttpWarnRequest(const char *type,Object*result,const char*msg);
    bool hookSocketMessage(Object*result);
    
    void socketConnectFinish();
    void socketReconnectFail();
    void socketDisconnect();
    void socketReceiveError();
private:
    //custom
    
};

#endif
