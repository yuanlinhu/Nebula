#pragma once

#include <WinSock2.h>
#include <event2/util.h>

#pragma  comment(lib,"ws2_32.lib")

class event_base;
class evconnlistener;

class Server
{
public:
	Server();
	~Server();


	void init(int port);
	void run();


	
	static void	accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
	static void accept_error_cb(struct evconnlistener *listener, void *ctx);
		
			
	static void test();



private:
	int m_port = 0;
	event_base *m_base = nullptr;
	evconnlistener* m_listener = nullptr;

	sockaddr_in m_sin;
};

