#ifndef _SocketHandler_H_
#define _SocketHandler_H_

#ifdef WIN32
#include <windows.h>
#else
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <unistd.h>
#endif // #ifdef WIN32

#ifdef WIN32
#pragma comment(lib, "ws2_32")

#ifndef socklen_t
#define socklen_t int
#endif

#ifndef	ssize_t
#define ssize_t long
#endif

#ifndef pid_t
#define pid_t int
#endif

#ifndef SHUT_RD
#define SHUT_RD			SD_RECEIVE
#define SHUT_WR			SD_SEND
#define SHUT_RDWR		2
#endif

#endif // #ifdef WIN32

#define MAX_REQUEST 255

class SocketHandler
{
public:
	// 构造与解除
	SocketHandler();                        // 创建一个空的Socket对象
	bool create(int type = SOCK_STREAM, int protocol = 0, int domain = PF_INET);
											// 为空的对象创建socket描述符
	~SocketHandler();								// 关闭连接和套接字
	void destroy();							// 关闭连接和套接字
	
	bool open_fd(int type = SOCK_STREAM, int protocol = 0, int domain = PF_INET);	
											// 先关闭原有的连接和套接字，然后创建新的socket
	void close_fd();						// 关闭套接字
	void attach_fd(int fd);					// 先关闭原有的连接和套接字，然后连接到指定的socket描述符
	void detach_fd();						// 仅将Socket对象的描述符设置为无效
	void shutdown_fd(int how = SHUT_RDWR);	// 关闭连接
	
	// 属性
	int get_fd() const { return _fd; }
	bool getlocalsock(struct sockaddr* localaddr, int* addrlen = NULL) const;
	bool getpeersock(struct sockaddr* peeraddr, int* addrlen = NULL) const;
	
	// 操作
	void reuse_addr(bool reuse = true);
	
	bool bind(struct sockaddr* addr, int addrlen = sizeof(struct sockaddr));
	bool bind(unsigned short port = 0, const char* addr = NULL, short family = AF_INET);
	
	bool listen(int backlog = MAX_REQUEST);
	
	bool accept(int* connected_fd, struct sockaddr* addr = NULL, int* addrlen = NULL);
	bool accept(SocketHandler* sock, struct sockaddr* addr = NULL, int* addrlen = NULL);
	
	bool connect(struct sockaddr* addr, int addrlen = sizeof(struct sockaddr));
	bool connect(const char* addr, unsigned short port, short family = AF_INET);
	
	bool send(const void* buf, const size_t& size, int flags = 0);
	bool send(const void* buf, size_t& size, int flags = 0);
	bool recv(void* buf, size_t& size, int flags = 0);
  
	/**  
	* 设置socket的阻塞状态
	* @param yes为TRUE，设置为非阻塞模式；false，则设置为阻塞模式  
	* @return
	*/
	void set_block(bool bblock = true);
	bool get_block() { return _block; }

public:
	/*
	 * 工具
	 */
	// 装载和卸载socket库
	static bool load_library();
	static bool unload_library();

	static struct hostent* gethost(const char* name) { return ::gethostbyname(name); }
	static struct hostent* gethost(const char* addr, int len, int family = AF_INET) 
	{ return ::gethostbyaddr(addr, len, family); }
	
	static struct servent* getserv(const char* name, const char* protocol = NULL) 
	{ return ::getservbyname(name, protocol); }
	static struct servent* getserv(int port, const char* protocol = NULL) 
	{ return ::getservbyport(port, protocol); } 
 
	static bool is_dot_dec_ip(const char* ipstr);
	
private:
	// 实现
	bool _send_aux(bool is_const, const void* buf, size_t& size, int flags);
	bool _recv_aux(bool is_const, void* buf, size_t& size, int flags);
	bool _sendto_aux(bool is_const, const void* buf, size_t& size, struct sockaddr* to, socklen_t addrlen, int flags);
	bool _sendto_aux(bool is_const, const void* buf, size_t& size, unsigned short port, const char* addr, int flags);
	bool _recvfrom_aux(bool is_const, void* buf, size_t& size, struct sockaddr* from, socklen_t* addrlen, int flags);
	bool _recvfrom_aux(bool is_const, void* buf, size_t& size, unsigned short* port, char* addr, int flags);
	
private:
	// 禁止的操作
	SocketHandler(const SocketHandler& rhs);
	SocketHandler& operator =(const SocketHandler& rhs);
	
protected:
	// 数据成员
	int _fd;
	bool _block;
};

#endif // #ifndef _SocketHandler_H_

 
 

 