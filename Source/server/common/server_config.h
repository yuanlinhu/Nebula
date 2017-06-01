
#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include <string>

class ServerConfig
{
public:
    ServerConfig();
    ~ServerConfig();

    void setServerConfig(int id, std::string& ip, int port);

    int get_id();
    std::string& get_ip();
    int get_port();

private:
    int m_id;
    std::string m_ip;
    int m_port;
};

#endif  //__SERVER_CONFIG_H__