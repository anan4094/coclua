#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

#ifdef WIN32
#include <windows.h>
#else
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "socket.h"

#ifdef WIN32
#define EINTR2		WSAEINTR
#endif // #ifdef WIN32

#define errputs puts

#ifndef MAX_BUF_SIZE
#define MAX_BUF_SIZE		1024
#endif

#ifndef MAX_STR_LEN
#define MAX_STR_LEN			254
#endif

#define P(x) cout << (x) << endl
#define F(str, file) \
	{ \
		char cmd[MAX_BUF_SIZE]; \
		sprintf(cmd, "echo \'%s\' >> %s", str, file); \
		system(cmd); \
		
#define ASSERT_NOT(x) \
	if (x) \
	{ \
		perror("ERROR"); \
		exit(1); \
	}

SocketHandler::SocketHandler() : _fd(-1), _block(true)
{
	
}

bool SocketHandler::create(int type /*= SOCK_STREAM*/, int protocol /*= 0*/, int domain /*= PF_INET*/)
{
	_fd = ::socket(domain, type, protocol);
	if (_fd == -1)
	{
		errputs("Error: ");
		errputs(strerror(errno));
		return false;
	}
	return true;
}

SocketHandler::~SocketHandler()
{	
	destroy();
}

void SocketHandler::destroy()
{
	if (_fd != -1)
	{
		::shutdown(_fd, SHUT_RDWR);
#ifdef WIN32
		::closesocket(_fd);
#else
		::close(_fd);
#endif // #ifdef WIN32
		_fd = -1;
		_block = true;
	}
}

bool SocketHandler::open_fd(int type /*= SOCK_STREAM*/, int protocol /*= 0*/, int domain /*= PF_INET*/)
{
	if (_fd != -1)
	{
		::shutdown(_fd, SHUT_RDWR);
#ifdef WIN32
		::closesocket(_fd);
#else
		::close(_fd);
#endif // #ifdef WIN32
		_fd = -1;
		_block = true;
	}
	_fd = ::socket(domain, type, protocol);
	return _fd == -1 ? false : true;
}

void SocketHandler::close_fd()
{
	if (_fd != -1)
	{
#ifdef WIN32
		::closesocket(_fd);
#else
		::close(_fd);
#endif // #ifdef WIN32
		_fd = -1;
		_block = true;
	}
}

void SocketHandler::attach_fd(int fd)
{
	if (_fd != -1)
	{
		::shutdown(_fd, SHUT_RDWR);
#ifdef WIN32
		::closesocket(_fd);
#else
		::close(_fd);
#endif // #ifdef WIN32
		_fd = -1;
		_block = true;
	}
	_fd = fd;
}

void SocketHandler::detach_fd()
{
	_fd = -1;
	_block = true;
}

void SocketHandler::shutdown_fd(int how /*= SHUT_RDWR*/)
{
	if (_fd != -1)
	{
		::shutdown(_fd, how);
	}
}

bool SocketHandler::getlocalsock(struct sockaddr* localaddr, int* addrlen /*= NULL*/) const
{
	if (_fd == -1)
		return false;

	int len = sizeof(struct sockaddr);
	if (addrlen == NULL)
		addrlen = &len;
	int result = ::getsockname(_fd, localaddr, (socklen_t *)addrlen);
	
	return result == -1 ? false : true;
}

bool SocketHandler::getpeersock(struct sockaddr* peeraddr, int* addrlen /*= NULL*/) const
{
	if (_fd == -1)
		return false;
		
	int len = sizeof(struct sockaddr);
	if (addrlen == NULL)
		addrlen = &len;
	int result = ::getpeername(_fd, peeraddr, (socklen_t *)addrlen);
	
	return result == -1 ? false : true;
}

void SocketHandler::reuse_addr(bool reuse /*= true*/)
{
#ifdef WIN32
	char open;
#else
	int open;
#endif // #ifdef WIN32
	
	open = reuse ? 1 : 0;
	socklen_t optlen = sizeof(open);
	::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &open, optlen);
}

bool SocketHandler::bind(struct sockaddr* addr, int addrlen /*= sizeof(struct sockaddr)*/)
{
	if (_fd == -1)
		return false;
		
	int result = ::bind(_fd, addr, addrlen);
	
	return result == -1 ? false : true;
}

bool SocketHandler::bind(unsigned short port /*= 0*/, const char* addr /*= NULL*/, short family /*= AF_INET*/)
{
	if (_fd == -1)
	{
		return false;
	}
	
	sockaddr_in my_addr = { sizeof(struct sockaddr_in) };
	my_addr.sin_family = family;
	my_addr.sin_port = htons(port);
	if (addr == NULL)
		my_addr.sin_addr.s_addr = INADDR_ANY;
	else 
	{ 
		if (is_dot_dec_ip(addr)) 
		{ 
			my_addr.sin_addr.s_addr = inet_addr(addr); 
		} 
		else 
		{ 
			hostent* he = ::gethostbyname(addr); 
			if (he == NULL) 
			{ 
				return false; 
			} 
			memcpy(&my_addr.sin_addr, he->h_addr_list[0], he->h_length); 
		} 
	}
	
	int addrlen = sizeof(struct sockaddr_in);
	int result = ::bind(_fd, (struct sockaddr*)&my_addr, addrlen);
	return result == -1 ? false : true;
}

bool SocketHandler::listen(int backlog /*= MAX_REQUEST*/)
{
	if (_fd == -1)
		return false;
		
	int result = ::listen(_fd, backlog);
	
	return result == -1 ? false : true;
}

bool SocketHandler::accept(int* connected_fd, struct sockaddr* addr /*= NULL*/, int* addrlen /*= NULL*/)
{
	assert(connected_fd != NULL);
	
	if (_fd == -1)
		return false;
	
	*connected_fd = ::accept(_fd, addr, (socklen_t *)addrlen);
	
	return *connected_fd == -1 ? false : true;
}

bool SocketHandler::accept(SocketHandler* sock, struct sockaddr* addr /*= NULL*/, int* addrlen /*= NULL*/)
{
	assert(sock != NULL);

	if (sock->_fd != -1)
		sock->detach_fd();
		
	if (_fd == -1)
		return false;
		
	sock->_fd = ::accept(_fd, addr, (socklen_t *)addrlen);
	
	return sock->_fd == -1 ? false : true;
}

bool SocketHandler::connect(struct sockaddr* addr, int addrlen /*= sizeof(struct sockaddr)*/)
{
	if (_fd == -1)
		return false;
	
	int result = ::connect(_fd, addr, addrlen);
	
	return result == -1 ? false : true;
}

bool SocketHandler::connect(const char* addr, unsigned short port, short family /*= AF_INET*/)
{
	if (_fd == -1)
		return false;
		
	if (addr == NULL)
		return false;
		
	sockaddr_in my_addr;
	my_addr.sin_family = family;
	my_addr.sin_port = htons(port);
	 
	if (is_dot_dec_ip(addr)) 
	{ 
		my_addr.sin_addr.s_addr = inet_addr(addr); 
	} 
	else 
	{ 
		hostent* he = ::gethostbyname(addr); 
		if (he == NULL) 
		{ 
			return false; 
		} 
		memcpy(&my_addr.sin_addr, he->h_addr_list[0], he->h_length); 
	}
	
	int addrlen = sizeof(struct sockaddr);
	int result = ::connect(_fd, (struct sockaddr*)&my_addr, addrlen);
	
	return result == -1 ? false : true;
}

void SocketHandler::set_block(bool block /*= true*/)
{
	_block = block;
	
	if (_fd == -1)
		return;
		
#ifdef WIN32
	u_long b = block ? 1 : 0;
	::ioctlsocket(_fd, FIONBIO, &b);
#else
	int flag;
	flag = ::fcntl(_fd, F_GETFL, 0);
	if (block)
		flag &= ~O_NONBLOCK;
	else
		flag |= O_NONBLOCK;
	::fcntl(_fd, F_SETFL, flag);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// private methodes

bool SocketHandler::_send_aux(bool is_const, const void* buf, size_t& size, int flags)
{	
	ssize_t new_size;
#ifdef WIN32
	while ((new_size = ::send(_fd, (const char*)buf, size, flags)) == -1 && errno == EINTR2);
#else
	while ((new_size = ::send(_fd, (const char*)buf, size, flags)) == -1 && errno == EINTR);
#endif 
	
	if (!is_const)
		size = new_size;
	return new_size == -1 ? false : true;
}

bool SocketHandler::_recv_aux(bool is_const, void* buf, size_t& size, int flags)
{
	ssize_t new_size;
#ifdef WIN32
	while ((new_size = ::recv(_fd, (char*)buf, size, flags)) == -1 && errno == EINTR2);
#else
	while ((new_size = ::recv(_fd, (char*)buf, size, flags)) == -1 && errno == EINTR);
#endif 
	//while ((new_size = ::recv(_fd, (char*)buf, size, flags)) == -1 && errno == EINTR2);
	if (!is_const)
		size = new_size;

	return new_size == -1 ? false : true; // 注意：连接被优雅地断开时new_size == 0
}

bool SocketHandler::_sendto_aux(bool is_const, const void* buf, size_t& size, struct sockaddr* to, socklen_t addrlen, int flags)
{
	ssize_t new_size;
#ifdef WIN32
	while ((new_size = ::sendto(_fd, (const char*)buf, size, flags, to, addrlen)) == -1 && errno == EINTR2);
#else
	while ((new_size = ::sendto(_fd, (const char*)buf, size, flags, to, addrlen)) == -1 && errno == EINTR);
#endif 
	//while ((new_size = ::sendto(_fd, (const char*)buf, size, flags, to, addrlen)) == -1 && errno == EINTR2);
	if (!is_const)
	{
		size = new_size;
	}
	
	return new_size == -1 ? false : true;
}

bool SocketHandler::_sendto_aux(bool is_const, const void* buf, size_t& size, unsigned short port, const char* addr, int flags)
{
	sockaddr_in my_addr = { sizeof(struct sockaddr_in) };
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	if (addr == NULL)
		my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	else 
	{ 
		if (is_dot_dec_ip(addr)) 
		{ 
			my_addr.sin_addr.s_addr = inet_addr(addr); 
		} 
		else 
		{ 
			hostent* he = ::gethostbyname(addr); 
			if (he == NULL) 
			{ 
				return false; 
			} 
			memcpy(&my_addr.sin_addr, he->h_addr_list[0], he->h_length); 
		} 
	}
	
	socklen_t addrlen = sizeof(sockaddr_in);
		
	return _sendto_aux(is_const, buf, size, (struct sockaddr*)&my_addr, addrlen, flags);
}

bool SocketHandler::_recvfrom_aux(bool is_const, void* buf, size_t& size, struct sockaddr* from, socklen_t* addrlen, int flags)
{
	ssize_t new_size;
#ifdef WIN32
	while ((new_size = ::recvfrom(_fd, (char*)buf, size, flags, from, (socklen_t *)addrlen)) == -1 && errno == EINTR2);
#else
	while ((new_size = ::recvfrom(_fd, (char*)buf, size, flags, from, (socklen_t *)addrlen)) == -1 && errno == EINTR);
#endif 
	//while ((new_size = ::recvfrom(_fd, (char*)buf, size, flags, from, (socklen_t *)addrlen)) == -1 && errno == EINTR2);
	if (!is_const)
	{
		size = new_size;
	}
	
	return new_size == -1 ? false : true;
}

bool SocketHandler::_recvfrom_aux(bool is_const, void* buf, size_t& size, unsigned short* port, char* addr, int flags)
{
	struct sockaddr_in from;
	socklen_t addrlen;
	if (!_recvfrom_aux(is_const, buf, size, (struct sockaddr*)&from, &addrlen, flags))
		return false;
		
	if (port != NULL)
		*port = from.sin_port;
	if (addr != NULL)
		strcpy(addr, inet_ntoa(from.sin_addr));
	
	return true;
}

bool SocketHandler::load_library()
{
#ifdef WIN32
	WORD wVersion = MAKEWORD(1,1);
	WSADATA wsaData;
	if (WSAStartup(wVersion,&wsaData) != 0)
	{
		return false;
	}
#endif // #ifdef WIN32
	return true;
}

bool SocketHandler::unload_library()
{
#ifdef WIN32
	if (WSACleanup() != 0)
	{
		return false;
	}
#endif // #ifdef WIN32
	return true;
} 
 
bool SocketHandler::is_dot_dec_ip(const char* ipstr) 
{ 
	assert(ipstr != NULL); 
 
	if (strlen(ipstr) < 7 || strlen(ipstr) > 15) 
	{ 
		return false; 
	} 
 
	int ndot = 0; 
	const char* p; 
	for (p = ipstr; *p != '\0'; ++p) 
	{ 
		if (*p != '.' && (*p < '0' || *p > '9')) 
		{ 
			return false; 
		} 
		if (*p == '.') 
		{ 
			++ndot; 
		} 
	} 
 
	if (ndot != 3) 
	{ 
		return false; 
	} 
	if (ipstr[0] == '.' || ipstr[strlen(ipstr) - 1] == '.') 
	{ 
		return false; 
	} 
	if (strstr(ipstr, "..") != NULL) 
	{ 
		return false; 
	} 
 
	char* buf = new char[strlen(ipstr) + 1]; 
	strcpy(buf, ipstr); 
	p = strtok(buf, "."); 
	while (p != NULL) 
	{ 
		int n = atoi(p); 
		if (n > 255) 
		{ 
			delete buf; 
			return false; 
		} 
 
		p = strtok(NULL, "."); 
	} 
	delete buf; 
 
	return true; 
}

bool SocketHandler::send(const void* buf, const size_t& size, int flags /*= 0*/)
{
	 return _send_aux(true, buf, const_cast<size_t&>(size), flags);
}

bool SocketHandler::send(const void* buf, size_t& size, int flags /*= 0*/)
{
	return _send_aux(false, buf, size, flags);
}

bool SocketHandler::recv(void* buf, size_t& size, int flags /*= 0*/)
{
	return _recv_aux(false, buf, size, flags); 
}
