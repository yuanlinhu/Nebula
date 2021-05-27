#pragma once

#include <WinSock2.h>
#include <event2/util.h>
#include <map>

using namespace std;

#pragma  comment(lib,"ws2_32.lib")

class event_base;
class evconnlistener;
class ClientConnection;
class bufferevent;

class Server
{
public:
	Server();
	~Server();


	void init(int port);
	void run();

	void handle_close(bufferevent *bev);
	void handle_accept(evutil_socket_t fd, struct sockaddr *address, int socklen);


	
	static void	accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
	static void accept_error_cb(struct evconnlistener *listener, void *ctx);
		
			
	static void test();



	static void socket_read_cb(bufferevent *bev, void *arg);
	static void socket_event_cb(bufferevent *bev, short events, void *arg);


private:
	int m_port = 0;
	event_base *m_base = nullptr;
	evconnlistener* m_listener = nullptr;
	sockaddr_in m_sin;


	std::map<int, ClientConnection*>	m_client_list;
};

