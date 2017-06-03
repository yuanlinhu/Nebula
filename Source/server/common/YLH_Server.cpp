

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
,m_connect_manager(NULL)
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

ClientSockManager* YLH_Server::get_client_manager()
{
    return m_client_manager;
}

ClientSockManager* YLH_Server::get_connect_manager()
{
    return m_connect_manager;
}

void YLH_Server::init_common()
{
    m_event_base = event_base_new();
    if(NULL == m_event_base)
    {
        cout<<"YLH_Server::init m_event_base = NULL"<<endl;
    }


    m_client_manager = new ClientSockManager();
    m_connect_manager = new ClientSockManager();
}

void YLH_Server::run()
{
    cout<<"server has started !"<<endl;
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


void YLH_Server::init_connection(const std::string& connect_ip, int connect_port)
{
    m_connect_ip    = connect_ip;
    m_connect_port  = connect_port;
//    m_client_id = client_id;

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = m_connect_port;
    inet_aton(m_connect_ip.c_str(), &server_addr.sin_addr);


    bufferevent* new_bev = bufferevent_socket_new(m_event_base, -1, BEV_OPT_CLOSE_ON_FREE);


    bufferevent_socket_connect(new_bev, (sockaddr*)&server_addr, sizeof(server_addr));

    bufferevent_setcb(new_bev, server_msg_cb, NULL, socket_event_cb, (void*)this);
    bufferevent_enable(new_bev, EV_READ | EV_PERSIST);

    this->add_sock_client_by_connect((sockaddr*)&server_addr, new_bev);
}

void YLH_Server::init_cmd()
{
    m_ev_cmd = event_new(m_event_base, STDIN_FILENO, EV_READ | EV_PERSIST, cmd_msg_cb, (void*)this);
    event_add(m_ev_cmd, NULL);
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


    server->add_sock_client_by_listen(fd, sock, new_conn_bev);
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
    else if(events & BEV_EVENT_CONNECTED)
    {
        cout<<"client has connected to server "<<endl;
        return;
    }
    //这将自动close套接字和free读写缓冲区
    bufferevent_free(bev);
}

void YLH_Server::add_sock_client_by_listen(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev)
{
    m_client_manager->add_client_sock(sock_fd, sock, bev);
}

void YLH_Server::add_sock_client_by_connect(sockaddr* sock, bufferevent *bev)
{
    m_connect_manager->add_client_sock(1, sock, bev);
}


void YLH_Server::hand_input(void* msg, int len)
{
    CommonMsg* client_msg = (CommonMsg*)msg;

    cout<<"YLH_Server::hand_input client_msg->id: "<<client_msg->id<<endl;
    cout<<"YLH_Server::hand_input client_msg->type: "<<client_msg->type<<endl;
    cout<<"YLH_Server::hand_input client_msg->sub_type: "<<client_msg->sub_type<<endl;

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

        bufferevent_write(temp_client->get_bev(), &retMsg, sizeof(retMsg) );
    }


}

void YLH_Server::cmd_msg_cb(int fd, short events, void* args)
{
    char msg[1024] = {0};

    int ret = read(fd, msg, sizeof(msg));
    if(ret < 0)
    {
        cout<<"cmd_msg_cb read error"<<endl;
        return;
    }

    cout<<"cmd_msg_cb msg: "<<msg<<endl;

    YLH_Server* server = (YLH_Server*)args;

    CommonMsg newMsg;
    newMsg.id = 111;//server->get_client_id();
    newMsg.type = 222;//server->get_port();
    newMsg.sub_type = 333;

    server->broad_to_all_server(&newMsg, sizeof(newMsg));


//    ClientSockManager* client_sock_manager = server.get_connect_manager();
//    if(NULL == client_sock_manager)
//    {
//        cout<<"YLH_Server::cmd_msg_cb client_sock_manager = NULL"<<endl;
//        return;
//    }

//    std::vector<ClientSock*> server_list;
//    client_sock_manager->get_client_list(server_list);
//
//    std::vector<ClientSock*>::iterator iter;
//    for(iter = server_list.begin(); iter != server_list.end(); ++iter)
//    {
//        ClientSock* sock = *iter;
//        if(NULL == sock)
//        {
//            continue;
//        }
//
//        bufferevent* bev = sock->get_bev();
//
//    }
//



//    CommonMsg newMsg;
//    newMsg.id = client->get_client_id();
//    newMsg.type = client->get_port();
//    newMsg.sub_type = 1;
//
//    bufferevent_write(bev, &newMsg, sizeof(newMsg));

}

void YLH_Server::broad_to_all_server(void* msg, int len)
{
    ClientSockManager* client_sock_manager = this->get_connect_manager();
    if(NULL == client_sock_manager)
    {
        cout<<"YLH_Server::cmd_msg_cb client_sock_manager = NULL"<<endl;
        return;
    }

    std::vector<ClientSock*> server_list;
    client_sock_manager->get_client_list(server_list);

    std::vector<ClientSock*>::iterator iter;
    for(iter = server_list.begin(); iter != server_list.end(); ++iter)
    {
        ClientSock* sock = *iter;
        if(NULL == sock)
        {
            continue;
        }

        bufferevent* bev = sock->get_bev();
        if(NULL == bev)
        {
            continue;
        }

        bufferevent_write(bev, msg, len);
    }
}

void YLH_Server::server_msg_cb(bufferevent* bev, void* args)
{
    char msg[1024] = {0};

    int len = bufferevent_read(bev, msg, sizeof(msg));

    YLH_Server* client = (YLH_Server*)args;
    client->hand_input(msg, len);
}