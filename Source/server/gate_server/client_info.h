
#ifndef __CLIENT_INFO_H_
#define __CLIENT_INFO_H_

#include <event2/util.h>
#include <string>

struct bufferevent;

class ClientInfo
{
public:
    ClientInfo();
    ~ClientInfo();


    void set_client_info(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev);

    bufferevent*    get_bev();
private:
    int             m_sock_fd;
    std::string     m_ip;
    int             m_port;
    bufferevent*    m_bev;
};

#endif  //__CLIENT_INFO_H_
