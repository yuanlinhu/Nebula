
#ifndef __SERVER_CONFIG_MANAGER_H__
#define __SERVER_CONFIG_MANAGER_H__

#include <map>
#include <string>

class ServerConfig;

class ServerConfigManager
{
public:
    ServerConfigManager();
    ~ServerConfigManager();

    void addServerConfig(int id, std::string& ip, int port);

    ServerConfig* get_server_config(int id);


private:
    std::map<int, ServerConfig*> m_server_list;
};

#endif  //__SERVER_CONFIG_MANAGER_H__