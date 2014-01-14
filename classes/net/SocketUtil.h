//
//  socketUtil.h
//  coclua
//
//  Created by anan on 1/9/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#ifndef __SocketUtil__
#define __SocketUtil__
#include "cocos2d.h"
#include "pthread.h"
#include <list>
USING_NS_CC;
using namespace std;
typedef unsigned int lint;
class RequestManager;
class SocketHandler;

enum SocketState{
	ESOCKET_NOP,
	ESOCKET_CONNECT_START, //连接开始
	ESOCKET_CONNECT_SUC, //连接成功
	ESOCKET_CONNECT_FAIL, //连接失败
    ESOCKET_RECONNECT_FAIL, //重接失败
	ESOCKET_RECEIVEDATA, //接收数据
	ESOCKET_DISCONNECTFROMCLIENT, //客户端主动断开连接
	ESOCKET_DISCONNECTFROMSERVER, //服务端主动断开连接
    
    ESOCKET_RECEIVE_ERROR
    
};

class SocketUtil :public Object{
private:
    std::string m_pServerIp;
	unsigned short m_serverPort;
	bool m_bIsConnect;
	RequestManager* m_pManager;
	SocketState m_socketState;
	SocketHandler* m_pSocketHandle;
    // 互斥对象
	pthread_mutex_t m_mutexForHandle;
    // 线程ID
	pthread_t m_threadConnect;
    bool m_bSchedulerBegin;
    list<char*> m_objectList;
    char *m_pRecvBuf;
    int m_nSendBufLength;
    int m_nRecvBufLength;
    int m_bufSize;
public:
    SocketUtil(std::string ip, unsigned short port, RequestManager* manager);
    int initAndConnect();
    void threadStartConnect();
    int recvData();
    
    void executeRender(float dt);
    void addData(const char* msg);
    void crashRender();
    
    static void* threadStartConnect(void* param);
};

#endif
