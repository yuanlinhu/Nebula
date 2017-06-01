
#include "server_config_manager.h"
#include "server_config.h"

ServerConfigManager::ServerConfigManager()
{

}

ServerConfigManager::~ServerConfigManager()
{

}

void ServerConfigManager::addServerConfig(int id, std::string& ip, int port)
{
    ServerConfig* exist_config = this->get_server_config(id);
    if(NULL != exist_config)
    {
        return;
    }

    ServerConfig* new_config = new ServerConfig();
    new_config->setServerConfig(id, ip, port);

    m_server_list[id] = new_config;
}

ServerConfig* ServerConfigManager::get_server_config(int id)
{
    ServerConfig* ret = NULL;

    std::map<int, ServerConfig*>::iterator iter = m_server_list.find(id);
    if(iter != m_server_list.end())
    {
        ret = iter->second;
    }

    return ret;
}
