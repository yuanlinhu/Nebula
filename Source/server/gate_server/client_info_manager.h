

#ifndef __CLIENT_INFO_MANAGER_H__
#define __CLIENT_INFO_MANAGER_H__

#include <map>
#include <string>
#include <vector>


#include <event2/util.h>

struct bufferevent;

class ClientInfo;

class ClientInfoManager
{
public:
    ClientInfoManager();
    ~ClientInfoManager();

    void add_client_info(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev);

    ClientInfo* get_client_info(evutil_socket_t sock_fd);

    void get_client_list(std::vector<ClientInfo*>& client_list);

private:
    std::map<evutil_socket_t, ClientInfo*> m_client_list;
};

#endif  //__CLIENT_INFO_MANAGER_H__