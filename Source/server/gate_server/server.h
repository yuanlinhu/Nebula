

#ifndef __SERVER_H_
#define __SERVER_H_

#include <string>

class Server
{
public:
	int tcp_connect_server(std::string server_ip, int port);

public:
	void cmd_msg_cb(int fd, short events, void* args);
	void server_msg_cb(int fd, short events, void* args);
	void event_cb(int fd, short events, void* args);
};


#endif	//__SERVER_H_