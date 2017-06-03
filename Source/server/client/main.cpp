#include <iostream>

#include <stdio.h>

#include "client.h"
#include "YLH_Server.h"
#include "server_define.h"

using namespace std;



int main(int argc, char** argv)
{
//    std::string ip("192.168.0.101");
    std::string ip("192.168.18.76");
    int port = 9999;

//	int client_id = 0;
//
//	sscanf(argv[1],"%d",&client_id);
//
//    Client client;
//	client.init(ip, port, client_id);

    YLH_Server server(SMT_GAME);
    server.init_common();
    server.init_cmd();
    server.init_connection(ip, port);

    server.run();
    return 0;
}
