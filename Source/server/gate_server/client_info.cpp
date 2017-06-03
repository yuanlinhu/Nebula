

#include "client_info.h"


ClientInfo::ClientInfo()
:m_sock_fd(0)
,m_port(0)
,m_bev(NULL)
{

}

ClientInfo::~ClientInfo()
{

}


void ClientInfo::set_client_info(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev)
{
    m_sock_fd = sock_fd;
    m_ip;
    m_port;
    m_bev = bev;
}

bufferevent* ClientInfo::get_bev()
{
    return m_bev;
}