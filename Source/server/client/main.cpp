#include <iostream>



#include "client.h"

using namespace std;



int main(int argc, char** argv)
{
    std::string ip("127.0.0.1");
    int port = 9999;

    Client client;
	client.init(ip, port);

    return 0;
}
