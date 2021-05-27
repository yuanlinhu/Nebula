#include "Server.h"
#include <event2/listener.h>
#include <iostream>
#include <string>
using namespace std;

Server::Server()
{
}


Server::~Server()
{
}

void Server::init(int port)
{
	WORD sockVersion = MAKEWORD(2, 2);         //请求2.2版本的WinSock库
											   // 用于接收Wjndows Socket的结构信息
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return ;
	}

	m_port = port;
	
	memset(&m_sin, 0, sizeof(m_sin));
	m_sin.sin_family = AF_INET;
	m_sin.sin_addr.s_addr = htonl(0);
	m_sin.sin_port = htons(m_port);


	m_listener = evconnlistener_new_bind(m_base, Server::accept_conn_cb, this,
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
		(struct sockaddr*)&m_sin, sizeof(m_sin));
	
	if (!m_listener) {
		perror("Couldn't create listener");
		return;
	}
	evconnlistener_set_error_cb(m_listener, Server::accept_error_cb);
}

void Server::accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx)
{
	cout << "accept_error_cb" << endl;
}

void Server::accept_error_cb(struct evconnlistener *listener, void *ctx)
{
	cout << "accept_error_cb" << endl;
}

void Server::test()
{
	Server server;
	server.init(1111);
	server.run();
}

void Server::run()
{
	event_base_dispatch(m_base);
}
