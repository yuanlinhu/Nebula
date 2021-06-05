

#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <string>
#include <WinSock2.h>

#pragma comment(lib,"Ws2_32.lib")

using namespace std;

struct event_base;
struct bufferevent;
struct event;

class Client
{
public:
	Client();
	void init(std::string ip, int port, int client_id);
	void init_command();
	void run();


	void init_timer();

    bufferevent* get_bev();
    int get_port();
    int get_client_id();

public:
	//int tcp_connect_server(std::string server_ip, int port);

	void clear();
	void hand_input(void* msg, int len);


	void handle_timer(int fd, short event);

	void send_msg(string str);
public:
	static void test();

	static void cmd_msg_cb(int fd, short events, void* args);
	static void server_msg_cb(bufferevent* bev, void* args);
	static void event_cb(bufferevent* bev, short events, void* args);

private:
	std::string m_ip;
	int m_port;
	int m_client_id;

	event_base* m_base = nullptr;
    bufferevent* m_bev = nullptr;
    event* m_ev_cmd = nullptr;
	event* m_event_timer = nullptr;
	
	int m_sock_fd = 0;
};


#endif	//__CLIENT_H_