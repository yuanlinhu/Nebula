#include <iostream>
#include <string>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>


#include "server.h"
//#include "server_config.h"
//#include "server_config_manager.h"

#include "YLH_Server.h"
#include "server_define.h"

#include "msg.pb.h"
//#include "common.pb.h"


using namespace std;


int main(int argc, char** argv)
{
	
	demo::msg msg_test;
	msg_test.set_msgtype(1);
	
//	common::head msg_head;
//	msg_head.set_headtype(100);
    //std::string ip("192.168.0.101");

//    std::string ip("192.168.18.76");
//    int port = 9999;
//
//    Server server;
//    server.init(ip, port);

    std::string ip("192.168.18.76");
    int port = 9999;

    YLH_Server server(SMT_GATE);
    server.init_common();
    server.init_timer(2);
    server.init_listener(ip, port);

    server.run();
    return 0;
}
