

#ifndef _YLH_SERVER_H_
#define _YLH_SERVER_H_

#include <string>

#include <event2/util.h>


struct event_base;
struct evconnlistener;


class YLH_Server
{
public:
    YLH_Server();
    ~YLH_Server();


public:
    void init_common();
    void init_listener(const std::string& ip, int port);


    void run();

public:
    static void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* args);
private:
    event_base*         m_event_base;
    evconnlistener*     m_listener;

    //监听相关
    std::string         m_listen_ip;
    int                 m_listen_port;

    //连接相关
};


#endif  //_YLH_SERVER_H_