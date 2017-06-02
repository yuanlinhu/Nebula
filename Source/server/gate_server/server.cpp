
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

}

Server::~Server()
{
    if(NULL != m_listener)
    {
        evconnlistener_free(m_listener);

    }

    if(NULL != m_base)
    {
        event_base_free(m_base);

    }
}

event_base* Server::get_event_base()
{
	return m_base;
}


void Server::init(std::string& ip, int port)
{
    cout<<"Server::init ip:["<<ip<<"]"<<endl;
	m_ip = ip;
	m_port = port;

	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = m_port;

    m_base = event_base_new();
    if(NULL == m_base)
    {
        cout<<"Server::init m_base = "<<m_base<<endl;
    }

	cout<<"Server::init evconnlistener_new_bind m_base = "<<m_base<<endl;
	cout<<"Server::init evconnlistener_new_bind this = "<<this<<endl;

    m_listener = evconnlistener_new_bind(m_base, listener_cb, (void*)this,
                                                        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                                        10, (sockaddr*)&sin,
                                                       sizeof(sockaddr_in));

    event_base_dispatch(m_base);
}

void Server::hand_input(void* msg, std::string& ret_msg)
{


	char* msg_str = (char*)msg;

	cout<<"Server::hand_input ===============>>>> msg = "<<(*msg_str)<<endl;

	ret_msg.clear();
	ret_msg.assign(msg_str);

	ret_msg += "  --from server";

	cout<<"Server::hand_input ===============>>>> msg_str = "<<msg_str<<endl;
}

void Server::listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* args)
{
    cout<<"Server::listener_cb args:["<<args<<"]"<<endl;
    printf("accept a client %d\n", fd);

    Server *server = (Server*)args;

	event_base* base = server->get_event_base();
    //为这个客户端分配一个bufferevent
    bufferevent *bev =  bufferevent_socket_new(base, fd,
                                               BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, Server::socket_read_cb, NULL, Server::socket_event_cb, (NULL));
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
}

void Server::socket_read_cb(bufferevent* bev, void* args)
{
    cout<<"Server::socket_read_cb args:["<<args<<"]"<<endl;
    int ii = 0;
    ii++;
    char msg[4096] = {0};

    size_t len = bufferevent_read(bev, msg, sizeof(msg)-1 );

    msg[len] = '\0';
   

	//char reply[4096] = {0};

	std::string reply;

	Server *server = (Server*)args;

	server->hand_input(msg, reply);

    bufferevent_write(bev, reply.c_str(), reply.size() );
}

void Server::socket_event_cb(bufferevent* bev, short events, void* args)
{
    cout<<"Server::socket_event_cb args:["<<args<<"]"<<endl;
    int ii = 0;
    ii++;

    if (events & BEV_EVENT_EOF)
        printf("connection closed\n");
    else if (events & BEV_EVENT_ERROR)
        printf("some other error\n");

    //这将自动close套接字和free读写缓冲区
    bufferevent_free(bev);
}