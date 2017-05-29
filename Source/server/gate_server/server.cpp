
#include "server.h"

#include <iostream>

#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<errno.h>  
#include<unistd.h>  

#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  

#include<event.h>  
#include<event2/bufferevent.h>  
#include<event2/buffer.h>  
#include<event2/util.h>  

#include <event2/listener.h>
#include <event2/thread.h>

Server::Server()
:m_base(NULL)
,m_listener(NULL)
{
    event_base* m_base = event_base_new();
}

Server::~Server()
{
    evconnlistener_free(m_listener);
    event_base_free(m_base);
}


void Server::init(std::string& ip, int port)
{
	m_ip = ip;
	m_port = port;

	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = m_port;


    evconnlistener* m_listener = evconnlistener_new_bind(m_base, listener_cb, m_base,
                                                        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                                        10, (sockaddr*)&sin,
                                                       sizeof(sockaddr_in));

    event_base_dispatch(m_base);
}

void Server::listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* addr, int socklen, void* args)
{
    int ii = 0;
    ii++;
}

void Server::socket_read_cb(bufferevent* bev, void* args)
{
    int ii = 0;
    ii++;
}

void Server::socket_event_cb(bufferevent* bev, void* arg)
{
    int ii = 0;
    ii++;
}