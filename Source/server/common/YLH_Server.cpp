

#include "YLH_Server.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>

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

#include "client_sock.h"
#include "client_sock_manager.h"

using std::cout;
using std::endl;


//testcode begin
struct CommonMsg
{
    int id;
    int type;
    int sub_type;

};
//testcode end

YLH_Server::YLH_Server()
:m_event_base(NULL)
,m_listener(NULL)
,m_client_manager(NULL)
{

}

YLH_Server::~YLH_Server()
{

}

event_base* YLH_Server::get_event_base()
{
    return m_event_base;
}

evconnlistener* YLH_Server::get_listener()
{
    return m_listener;
}

void YLH_Server::init_common()
{
    m_event_base = event_base_new();
    if(NULL == m_event_base)
    {
        cout<<"YLH_Server::init m_event_base = NULL"<<endl;
    }


    m_client_manager = new ClientSockManager();
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
    cout<<"Server::listener_cb fd:["<<fd<<"]"<<endl;

    YLH_Server *server = (YLH_Server*)args;

    event_base* base = server->get_event_base();

    //为这个客户端分配一个bufferevent
    bufferevent *new_conn_bev =  bufferevent_socket_new(base, fd,
                                               BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(new_conn_bev, YLH_Server::socket_read_cb, NULL, YLH_Server::socket_event_cb, (args));
    bufferevent_enable(new_conn_bev, EV_READ | EV_PERSIST);


    server->add_connect_info(fd, sock, new_conn_bev);
}

void YLH_Server::socket_read_cb(bufferevent* bev, void* args)
{
    cout<<"YLH_Server::socket_read_cb args:["<<args<<"]"<<endl;

    char msg[4096] = {0};
    size_t len = bufferevent_read(bev, msg, sizeof(msg)-1 );

    YLH_Server *server = (YLH_Server*)args;

    server->hand_input(msg, len);
}

void YLH_Server::socket_event_cb(bufferevent* bev, short events, void* args)
{
    cout<<"YLH_Server::socket_event_cb args:["<<args<<"]"<<endl;

    if (events & BEV_EVENT_EOF)
        printf("connection closed\n");
    else if (events & BEV_EVENT_ERROR)
        printf("some other error\n");

    //这将自动close套接字和free读写缓冲区
    bufferevent_free(bev);
}

void YLH_Server::add_connect_info(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev)
{
    m_client_manager->add_client_sock(sock_fd, sock, bev);
}



void YLH_Server::hand_input(void* msg, int len)
{
    CommonMsg* client_msg = (CommonMsg*)msg;

    cout<<"YLH_Server::hand_input msg_str:"<<client_msg<<endl;

    CommonMsg retMsg;
    retMsg.id = client_msg->id + 10;
    retMsg.type = client_msg->type;
    retMsg.sub_type = client_msg->sub_type;

    std::vector< ClientSock* > client_list;
    m_client_manager->get_client_list(client_list);

    std::vector<ClientSock*>::iterator iter;
    for(iter = client_list.begin(); iter != client_list.end(); ++iter)
    {
        ClientSock* temp_client = *iter;
        if(NULL == temp_client)
        {
            continue;
        }

        bufferevent_write(temp_client->get_bev(), msg_str, sizeof(*msg_str) );
    }


}