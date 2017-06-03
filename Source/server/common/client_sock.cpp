

#include "client_sock.h"


ClientSock::ClientSock()
:m_sock_fd(0)
,m_port(0)
,m_bev(NULL)
{

}

ClientSock::~ClientSock()
{

}


void ClientSock::set_client_sock(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev)
{
    m_sock_fd = sock_fd;
    m_ip;
    m_port;
    m_bev = bev;
}

bufferevent* ClientSock::get_bev()
{
    return m_bev;
}