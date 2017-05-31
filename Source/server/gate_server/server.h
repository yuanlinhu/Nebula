

#ifndef __SERVER_H_
#define __SERVER_H_

#include <string>

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


using namespace std;

struct evconnlistener;
struct bufferevent;
struct event_base;


class Server
{
public:
	Server();
    ~Server();
public:
	void init(std::string& ip, int port);
public:
	static void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* args);
	static void socket_read_cb(bufferevent* bev, void* args);
	static void socket_event_cb(bufferevent* bev, short events, void* arg);

private:
	int m_port;
	std::string m_ip;

    event_base* m_base;
    evconnlistener* m_listener;
};


#endif	//__SERVER_H_