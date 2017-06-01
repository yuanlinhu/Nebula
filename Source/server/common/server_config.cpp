
#include "server_config.h"


ServerConfig::ServerConfig()
:m_id(0)
,m_port(0)
{

}

ServerConfig::~ServerConfig()
{

}


void ServerConfig::setServerConfig(int id, std::string& ip, int port)
{
    m_id = id;
    m_ip = ip;
    m_port = port;
}

int ServerConfig::get_id()
{
    return m_id;
}


std::string& ServerConfig::get_ip()
{
    return m_ip;
}

int ServerConfig::get_port()
{
    return m_port;
}