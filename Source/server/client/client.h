

#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <string>

struct event_base;
struct bufferevent;

class Client
{
public:
	Client();
	void init(std::string& ip, int port, int client_id);

public:
	int tcp_connect_server(std::string server_ip, int port);

public:
	static void cmd_msg_cb(int fd, short events, void* args);
	static void server_msg_cb(bufferevent* bev, void* args);
	static void event_cb(bufferevent* bev, short events, void* args);

private:
	event_base* m_base;
	std::string m_ip;
	int m_port;
	int m_client_id;
};


#endif	//__CLIENT_H_