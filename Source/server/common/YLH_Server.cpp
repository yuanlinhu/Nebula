

#include "YLH_Server.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include <event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/listener.h>
#include <event2/thread.h>

using std::cout;
using std::endl;

YLH_Server::YLH_Server()
:m_event_base(NULL)
,m_listener(NULL)
{

}

YLH_Server::~YLH_Server()
{

}


void YLH_Server::init_common()
{
    m_event_base = event_base_new();
    if(NULL == m_event_base)
    {
        cout<<"YLH_Server::init m_event_base = NULL"<<endl;
    }
}

void YLH_Server::run()
{
    event_base_dispatch(m_event_base);
}

void YLH_Server::init_listener(const std::string& listen_ip, int listen_port)
{
    m_listen_ip = listen_ip;
    m_listen_port = listen_port;

    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = m_listen_port;


    m_listener = evconnlistener_new_bind(m_event_base,
                                         listener_cb, this,
                                         LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                         10,
                                         (sockaddr*)(&sin), sizeof(sockaddr_in));
}

void YLH_Server::listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* args)
{
//    cout<<"Server::listener_cb args:["<<args<<"]"<<endl;
//    printf("accept a client %d\n", fd);
//
//    Server *server = (Server*)args;
//
//    event_base* base = server->get_event_base();
//    //为这个客户端分配一个bufferevent
//    bufferevent *bev =  bufferevent_socket_new(base, fd,
//                                               BEV_OPT_CLOSE_ON_FREE);
//
//    bufferevent_setcb(bev, Server::socket_read_cb, NULL, Server::socket_event_cb, (args));
//    bufferevent_enable(bev, EV_READ | EV_PERSIST);
//
//
//    server->get_client_manager()->add_client_info(fd, sock, bev);
}