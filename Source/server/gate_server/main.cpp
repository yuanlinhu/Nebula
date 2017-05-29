#include <iostream>



#include "server.h"

using namespace std;



int main(int argc, char** argv)
{
    std::string ip("127.0.0.1");
    int port = 9999;

    Server server;
    server.init(ip, port);

    return 0;
}
