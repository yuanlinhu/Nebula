#pragma once

#include <WinSock2.h>
#include <event2/util.h>
#include <map>
#include <event2/event.h>
#include <thread>

using namespace std;

#pragma  comment(lib,"ws2_32.lib")

struct event_base;
struct evconnlistener;
class ClientConnection;
struct bufferevent;
struct event;

class Server
{
public:
	Server();
	~Server();


	void init(int port);
	void init_timer();
	void run();

	void handle_close(bufferevent *bev);
	void handle_accept(evutil_socket_t fd, sockaddr *address, int socklen);
	void handle_timer(int fd, short event);


	static void	accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
	static void accept_error_cb(struct evconnlistener *listener, void *ctx);
		
			
	static void test();

	static void thread_fun(event_base * args);

	static void socket_read_cb(bufferevent *bev, void *arg);
	static void socket_event_cb(bufferevent *bev, short events, void *arg);

	event_base *get_event_base();

private:
	int m_port = 0;
	event_base *m_base = nullptr;
	evconnlistener* m_listener = nullptr;
	sockaddr_in m_sin;
	event* m_event_timer = nullptr;

	std::map<int, ClientConnection*>	m_client_list;

	//std::thread* m_logic_thread = nullptr;
};

