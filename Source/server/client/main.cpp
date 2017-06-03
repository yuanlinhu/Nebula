#include <iostream>

#include <stdio.h>

#include "client.h"

using namespace std;



int main(int argc, char** argv)
{
//    std::string ip("192.168.0.101");
    std::string ip("192.168.18.76");
    int port = 9999;

	int client_id = 0;

	sscanf(argv[1],"%d",&client_id);

    Client client;
	client.init(ip, port, client_id);

    return 0;
}
