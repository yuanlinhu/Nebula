#include <iostream>



#include "server.h"
//#include "server_config.h"
//#include "server_config_manager.h"

using namespace std;



int main(int argc, char** argv)
{
//    ServerConfig serverConf;
//    ServerConfigManager server_conf_manager;

    std::string ip("192.168.0.101");
    int port = 9999;

    Server server;
    server.init(ip, port);

    return 0;
}
