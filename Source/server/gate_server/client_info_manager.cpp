

#include "client_info_manager.h"
#include "client_info.h"

ClientInfoManager::ClientInfoManager()
{

}

ClientInfoManager::~ClientInfoManager()
{

}

void ClientInfoManager::add_client_info(evutil_socket_t sock_fd, sockaddr* sock, bufferevent *bev)
{
    ClientInfo* exist_config = this->get_client_info(sock_fd);
    if(NULL != exist_config)
    {
        return;
    }

    ClientInfo* new_client = new ClientInfo();
    new_client->set_client_info(sock_fd, sock, bev);

    m_client_list[sock_fd] = new_client;
}

ClientInfo* ClientInfoManager::get_client_info(evutil_socket_t sock_fd)
{
    ClientInfo* ret = NULL;

    std::map<evutil_socket_t, ClientInfo*>::iterator iter = m_client_list.find(sock_fd);
    if(iter != m_client_list.end())
    {
        ret = iter->second;
    }

    return ret;
}

void ClientInfoManager::get_client_list(std::vector<ClientInfo*>& client_list)
{
    client_list.clear();

    std::map<evutil_socket_t, ClientInfo*>::iterator iter;
    for (iter = m_client_list.begin(); iter != m_client_list.end(); ++iter)
    {
        ClientInfo* temp_client = iter->second;
        if(NULL == temp_client)
        {
            continue;
        }
        client_list.push_back(temp_client);
    }
}
