#include <iostream>



#include "server.h"
//#include "server_config.h"
//#include "server_config_manager.h"

#include "YLH_Server.h"

using namespace std;



int main(int argc, char** argv)
{
    //std::string ip("192.168.0.101");

//    std::string ip("192.168.18.76");
//    int port = 9999;
//
//    Server server;
//    server.init(ip, port);

    std::string ip("192.168.18.76");
    int port = 9999;

    YLH_Server server;
    server.init_common();
    server.init_listener(ip, port);

    server.run();
    return 0;
}
