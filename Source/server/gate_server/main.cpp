#include <iostream>



#include "server.h"

using namespace std;



int main(int argc, char** argv)
{
    std::string ip("192.168.18.76");
    int port = 9999;

    Server server;
    server.init(ip, port);

    return 0;
}
