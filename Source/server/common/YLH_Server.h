

#ifndef _YLH_SERVER_H_
#define _YLH_SERVER_H_

#include <string>

#include <event2/util.h>

#include "server_define.h"


struct event;
struct event_base;
struct evconnlistener;
struct bufferevent;

class ClientSockManager;


class YLH_Server
{
public:
    YLH_Server(SERVER_MAIN_TYPE main_type);
    ~YLH_Server();

public:
    //getter setter
    event_base*         get_event_base();
    evconnlistener*     get_listener();


    ClientSockManager*  get_client_manager();
    ClientSockManager*  get_connect_manager();

public:
    //-------------------事件库

    //监听事件
    static void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* args);

    static void socket_read_cb(bufferevent* bev, void* args);

    static void server_msg_cb(bufferevent* bev, void* args);

    //定时器
    static void timeout_cb(int fd, short event, void *arg);

    //错误事件
    static void socket_event_cb(bufferevent* bev, short events, void* arg);

    //控制台事件
    static void cmd_msg_cb(int fd, short events, void* args);

public:
    //协议处理
    void hand_input(void* msg, int len);

public:
    //发协议相关函数
    void broad_to_all_server(void* msg, int len);

public:
    //初始化
    void init_common();
    void init_listener(const std::string& ip, int port);
    void init_connection(const std::string& connect_ip, int connect_port);
    void init_cmd();
    void init_timer(int second);

    void run();


private:
    //辅助函数

    //通过监听端口获得链接
    void add_sock_client_by_listen(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev);

    //通过主动请求获得链接
    void add_sock_client_by_connect(sockaddr* sock, bufferevent *bev);

private:
    SERVER_MAIN_TYPE    m_server_main_type;


    event_base*         m_event_base;
    evconnlistener*     m_listener;

    //监听相关
    std::string         m_listen_ip;
    int                 m_listen_port;
    ClientSockManager*  m_client_manager;

    //连接相关
    std::string         m_connect_ip;
    int                 m_connect_port;
    ClientSockManager*  m_connect_manager;


    //读取控制台
    event*              m_ev_cmd;

    //定时器
    event*              m_ev_timer;

private:
    YLH_Server();
    YLH_Server(const YLH_Server&);
    YLH_Server& operator=(const YLH_Server&);
};


#endif  //_YLH_SERVER_H_