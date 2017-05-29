
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
{

}


void Server::init()
{
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = m_port;
}

void Server::listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* addr, int socklen, void* args)
{

}

void Server::socket_read_cb(bufferevent* bev, void* args)
{

}

void Server::socket_event_cb(bufferevent* bev, void* arg)
{

}