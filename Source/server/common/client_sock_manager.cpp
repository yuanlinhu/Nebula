

#include "client_sock_manager.h"
#include "client_sock.h"

ClientSockManager::ClientSockManager()
{

}

ClientSockManager::~ClientSockManager()
{

}

void ClientSockManager::add_client_sock(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev)
{
    ClientSock* exist_config = this->get_client_sock(sock_fd);
    if(NULL != exist_config)
    {
        return;
    }

    ClientSock* new_client = new ClientSock();
    new_client->set_client_sock(sock_fd, sock, bev);

    m_client_list[sock_fd] = new_client;
}

ClientSock* ClientSockManager::get_client_sock(evutil_socket_t sock_fd)
{
    ClientSock* ret = NULL;

    std::map<evutil_socket_t, ClientSock*>::iterator iter = m_client_list.find(sock_fd);
    if(iter != m_client_list.end())
    {
        ret = iter->second;
    }

    return ret;
}

void ClientSockManager::get_client_list(std::vector<ClientSock*>& client_list)
{
    client_list.clear();

    std::map<evutil_socket_t, ClientSock*>::iterator iter;
    for (iter = m_client_list.begin(); iter != m_client_list.end(); ++iter)
    {
        ClientSock* temp_client = iter->second;
        if(NULL == temp_client)
        {
            continue;
        }
        client_list.push_back(temp_client);
    }
}
