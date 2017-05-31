#include <iostream>



#include "client.h"

using namespace std;



int main(int argc, char** argv)
{
    std::string ip("192.168.18.76");
    int port = 9999;

    Client client;
	client.init(ip, port);

    return 0;
}
