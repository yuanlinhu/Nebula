

#ifndef _YLH_SERVER_H_
#define _YLH_SERVER_H_

#include <string>

#include <event2/util.h>


struct event_base;
struct evconnlistener;
struct bufferevent;

class YLH_Server
{
public:
    YLH_Server();
    ~YLH_Server();

public:
    //getter setter
    event_base*         get_event_base();
    evconnlistener*     get_listener();


public:
    //事件库
    static void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* args);
    static void socket_read_cb(bufferevent* bev, void* args);
    static void socket_event_cb(bufferevent* bev, short events, void* arg);

public:
    //初始化
    void init_common();
    void init_listener(const std::string& ip, int port);

    void run();


private:
    //辅助函数

    //获得新的链接
    void add_connect_info(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev);

private:
    event_base*         m_event_base;
    evconnlistener*     m_listener;

    //监听相关
    std::string         m_listen_ip;
    int                 m_listen_port;

    //连接相关
};


#endif  //_YLH_SERVER_H_