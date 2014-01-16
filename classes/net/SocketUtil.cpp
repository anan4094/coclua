//
//  socketUtil.cpp
//  coclua
//
//  Created by anan on 1/9/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#include "SocketUtil.h"
#include "RequestManager.h"
#include "socket.h"
#include "JsonUtil.h"

USING_NS_CC;

SocketUtil::SocketUtil(std::string ip, unsigned short port, RequestManager* manager):m_pRecvBuf(nullptr),m_pSendBuf(nullptr),m_bufSize(1024),m_nSendBufLength(0),m_nRecvBufLength(0),m_bSchedulerBegin(false){
    m_pSocketHandle = nullptr;
	m_pServerIp = ip;
	m_serverPort = port;
	m_bIsConnect = false;
	m_pManager = manager;
	m_socketState = ESOCKET_NOP;
}

SocketUtil::~SocketUtil(){
    if (m_bSchedulerBegin) {
        Scheduler* pScheduler = CCDirector::getInstance()->getScheduler();
        pScheduler->unscheduleSelector(schedule_selector(SocketUtil::executeRender), this);
        m_bSchedulerBegin = false;
    }
    if (m_pSendBuf) {
        delete m_pSendBuf;
        m_pSendBuf = nullptr;
    }
    if (m_pRecvBuf) {
        delete m_pRecvBuf;
        m_pRecvBuf = nullptr;
    }
    closeAndDeleteSocket();
}

int SocketUtil::initAndConnect(){
    int errCode = 0;
    do{
        m_bIsConnect = false;
        // 初始化互斥对象
		pthread_mutex_init(&m_mutexForHandle, NULL);
		pthread_attr_t tAttr;
		errCode = pthread_attr_init(&tAttr);
        
		if(errCode!=0)break;
        //新线程不能用pthread_join()来同步，且在退出时自行释放所占用的资源
		errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
        
		if (errCode != 0) {
			pthread_attr_destroy(&tAttr);
			break;
		}
        //init socket
		m_pSocketHandle = new SocketHandler();
		SocketHandler::load_library();
		m_pSocketHandle->create();
        
        
        //create thread for connect sever
        errCode = pthread_create(&m_threadConnect, &tAttr, &SocketUtil::threadStartConnect, this);
        if (!m_bSchedulerBegin) {
            Scheduler* pScheduler = Director::getInstance()->getScheduler();
			pScheduler->scheduleSelector(schedule_selector(SocketUtil::executeRender), this, 0.05f, false);
            m_bSchedulerBegin = true;
        }
    }while(0);
    return errCode;
}

void SocketUtil::threadStartConnect()
{
//    printf("start connect\n");
	m_socketState = ESOCKET_CONNECT_START;
	bool isConnect = m_pSocketHandle->connect(m_pServerIp.c_str(), m_serverPort);
	if (isConnect)
	{
//		printf("connected\n");
		m_bIsConnect = true;
		m_socketState = ESOCKET_CONNECT_SUC;
	}
	else
	{
//		printf("connect fail===== %s %d\n", m_pServerIp.c_str(), m_serverPort);
		m_socketState = ESOCKET_CONNECT_FAIL;
		return ;
	}
	recvData();
}
int SocketUtil::recvData()
{
	char lengthInfo[1024 * 2];
	size_t nRevLength = 1024;
	int bufUsedLength = 0;
	size_t currentPoint = 0; //指针当前位置
	while(1)
	{
		if (!m_pSocketHandle)
		{
			//此时接口已经关闭
			return -1;
		}
		
		nRevLength = 1024;
		//循环接收数据
		//获得消息长度
		if (!m_pSocketHandle->recv(lengthInfo, nRevLength, 0))
		{
			//回调
//            printf("recv error ========%d", m_bIsConnect);
            if (m_bIsConnect == true && m_pSocketHandle != NULL) {
                m_bIsConnect = false;
                m_socketState = ESOCKET_RECEIVE_ERROR;
            }
			return 0;
            
		}
		if (nRevLength == 0)
		{
			//连接被断开
			m_bIsConnect = false;
			m_socketState = ESOCKET_DISCONNECTFROMSERVER;
			break;
		}
		//判断接收字符串
		if(!m_pRecvBuf)
		{
		    m_pRecvBuf = new char[m_bufSize];
			m_nRecvBufLength = m_bufSize;
			bufUsedLength = 0;
		}
        
		//判断当前剩余缓冲区是否够用
		if (nRevLength > m_nRecvBufLength - bufUsedLength)
		{
			m_pRecvBuf = (char*)realloc(m_pRecvBuf, nRevLength + bufUsedLength);
			m_nRecvBufLength = nRevLength + bufUsedLength;
			if (!m_pRecvBuf)
			{
				printf("error\n");
				return 0;
			}
		}
		//拼接字符串
		memcpy(m_pRecvBuf + bufUsedLength, lengthInfo, nRevLength);
		bufUsedLength += nRevLength;
        
		currentPoint = 0;
		long tempLength = ntohl(*((lint*)m_pRecvBuf)); //当前第一个消息长度
		int temremain = bufUsedLength - sizeof(lint);//减去存储长度的内存区域的字符串长度
		while (bufUsedLength > 0)
		{
			if (temremain >= tempLength)
			{
				char* jsonBuf = new char[tempLength + 1];
				memcpy(jsonBuf, m_pRecvBuf + sizeof(lint) + currentPoint, tempLength);
				jsonBuf[tempLength] = '\0';
                
				printf("socket recv: %s\n", jsonBuf);
				pthread_mutex_lock(&m_mutexForHandle);
				m_objectList.push_back(jsonBuf);
				m_socketState = ESOCKET_RECEIVEDATA;
				pthread_mutex_unlock(&m_mutexForHandle);
                
				//处理后修正相关数值
				bufUsedLength = bufUsedLength - tempLength - sizeof(lint);
				currentPoint += tempLength + sizeof(lint);
				if (bufUsedLength > 0)
				{
					//还有消息时，重新设置此时第一条消息长度
					tempLength = ntohl(*((lint*)(m_pRecvBuf + currentPoint)));
					temremain = bufUsedLength - sizeof(lint);
				}
			}
			else
			{
				break;
			}
		}
		if (currentPoint!=0 && bufUsedLength > 0)
		{
			memcpy(m_pRecvBuf, m_pRecvBuf + currentPoint, bufUsedLength);
		}
	}
	return 0;
}
void SocketUtil::sendMessage(const char* message)
{
//	printf("socket will send-->%s", message);
	if (!m_bIsConnect)
	{
//		printf("socket diconnet!!!!!!");
		return;
	}
	//添加长度
	size_t length = strlen(message);
	if (length + sizeof(int) > m_nSendBufLength)
	{
		if(m_pSendBuf)
		{
			delete[] m_pSendBuf;
			m_pSendBuf = NULL;
		}
        
		m_pSendBuf = new char[length+sizeof(int)];
        if (!m_pSendBuf) {
            printf("socket is err:%s===================", message);
            return;
        }
		m_nSendBufLength = length+sizeof(int);
	}
    
	*((lint*)m_pSendBuf) = htonl(length);
    
	memcpy(m_pSendBuf+sizeof(lint), message, length);
    
    bool bSend = m_pSocketHandle->send(m_pSendBuf, length + sizeof(lint));
        
    if (!bSend){
//        printf("send message \"%s\" fail", message);
    }
}

void SocketUtil::closeAndDeleteSocket()
{
	m_bIsConnect = false;
	// 加锁   避免在多线程中同时处理
	pthread_mutex_lock(&m_mutexForHandle);
	if (m_pSocketHandle)
	{
		m_pSocketHandle->destroy();
	}
	// 释放互斥锁
	pthread_mutex_unlock(&m_mutexForHandle);
    
	delete m_pSocketHandle;
    m_pSocketHandle = nullptr;
}

void SocketUtil::executeRender(float dt){
    switch (m_socketState)
	{
        case ESOCKET_CONNECT_START:
		{
			m_pManager->socketHandleState(ESOCKET_CONNECT_START);
			m_socketState = ESOCKET_NOP;
		}break;
        case ESOCKET_CONNECT_SUC:
		{
            m_pManager->socketHandleState(ESOCKET_CONNECT_SUC);
			m_socketState = ESOCKET_NOP;
		}break;
        case ESOCKET_CONNECT_FAIL:{
            Scheduler* pScheduler = CCDirector::getInstance()->getScheduler();
            pScheduler->unscheduleSelector(schedule_selector(SocketUtil::executeRender), this);
            m_bSchedulerBegin = false;
            m_pManager->socketHandleState(ESOCKET_CONNECT_FAIL);
			m_socketState = ESOCKET_NOP;
		}break;
        case  ESOCKET_RECEIVEDATA:
		{
			pthread_mutex_lock(&m_mutexForHandle);
			if (m_objectList.size() > 0)
			{
				m_pManager->socketReceiveFromServer(JsonUtil::objectWithString(m_objectList.front()));
				char* loader = m_objectList.front();
				if(loader){
                    delete loader;
                    loader = NULL;
                }
				m_objectList.pop_front();
			}
			if (m_objectList.size() == 0)
			{
				m_socketState = ESOCKET_NOP;
			}
			pthread_mutex_unlock(&m_mutexForHandle);
			
		}break;
        case ESOCKET_RECEIVE_ERROR:{
            m_pManager->socketHandleState(m_socketState);
			m_socketState = ESOCKET_NOP;
        }break;
        case ESOCKET_DISCONNECTFROMSERVER:{
            m_pManager->socketHandleState(m_socketState);
			m_socketState = ESOCKET_NOP;
		}break;
        default:
            break;
	}
}

void* SocketUtil::threadStartConnect(void *param){
    ((SocketUtil*) param)->threadStartConnect();
	return ((void*) 0);
}

void SocketUtil::addData(const char *msg){
    char* jsonBuf = new char[256];
    strcpy(jsonBuf, msg);
    pthread_mutex_lock(&m_mutexForHandle);
    m_objectList.push_back(jsonBuf);
    m_socketState = ESOCKET_RECEIVEDATA;
    pthread_mutex_unlock(&m_mutexForHandle);
}
