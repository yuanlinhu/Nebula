

#ifndef __CLIENT_SOCK_MANAGER_H__
#define __CLIENT_SOCK_MANAGER_H__

#include <map>
#include <string>
#include <vector>


#include <event2/util.h>

struct bufferevent;

class ClientSock;

class ClientSockManager
{
public:
    ClientSockManager();
    ~ClientSockManager();

    void add_client_sock(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev);

    ClientSock* get_client_sock(evutil_socket_t sock_fd);

    void get_client_list(std::vector<ClientSock*>& client_list);

private:
    std::map<evutil_socket_t, ClientSock*> m_client_list;
};

#endif  //__CLIENT_INFO_MANAGER_H__