#include "Server.h"
#include <event2/listener.h>
#include <iostream>
#include <string>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include "ClientConnection.h"
#include <WinSock2.h>
#include <thread>
#include <event2/thread.h>

#include "LogicThreadManager.h"
#include "LogicThread.h"

using namespace std;

Server* g_server = nullptr;

Server::Server()
{
	m_thread_mgr = new LogicThreadManager();
}


Server::~Server()
{
}

void Server::init_logic_thread(int thread_num)
{
	m_thread_mgr->init(thread_num);
}

void Server::init(int port)
{
	cout << "server start port: " << m_port << endl;

	WORD sockVersion = MAKEWORD(2, 2);         //请求2.2版本的WinSock库
											   // 用于接收Wjndows Socket的结构信息
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return ;
	}

	m_base = event_base_new();

	m_port = port;
	
	memset(&m_sin, 0, sizeof(m_sin));
	m_sin.sin_family = AF_INET;
	//m_sin.sin_addr.s_addr = htonl(0);
	m_sin.sin_port = htons(m_port);
	m_sin.sin_addr.s_addr = INADDR_ANY;


	m_listener = evconnlistener_new_bind(m_base, Server::accept_conn_cb, this,
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
		(struct sockaddr*)&m_sin, sizeof(m_sin));
	
	if (!m_listener) {
		perror("Couldn't create listener");
		return;
	}
	evconnlistener_set_error_cb(m_listener, Server::accept_error_cb);
	cout << "server started success~~~~!! port: " << m_port << endl;
}



void on_timer_cb(int fd, short event, void *arg)
{
	Server* server = (Server*)arg;
	server->handle_timer(fd, event);
}


void Server::init_timer()
{
	timeval tv;

	tv.tv_sec = 2;
	tv.tv_usec = 0;
	m_event_timer = event_new(m_base, -1, EV_TIMEOUT, on_timer_cb, this);
	evtimer_add(m_event_timer, &tv);
}

void Server::accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx)
{
	cout << "accept_conn_cb" << endl;

	Server* server = (Server*)ctx;
	server->handle_accept(fd, address, socklen);
}

void Server::accept_error_cb(struct evconnlistener *listener, void *ctx)
{
	cout << "accept_error_cb" << endl;
}

void Server::thread_fun(event_base * args)
{

	event_base *base = (event_base*)args;
	//event_base* thread_base = event_base_new();
	event_base_dispatch(base);
}

void Server::test()
{
	evthread_use_windows_threads();

	Server server;
	server.init(11111);
	//server.init_timer();
	server.init_logic_thread(1);

	g_server = &server;
	
	server.run();
}

event_base* Server::get_event_base()
{
	return m_base;
}

void Server::handle_input(bufferevent *bev, char* msg, size_t len)
{
	int fd = bufferevent_getfd(bev);
	LogicThread* thread_info = m_thread_mgr->get_thread(fd);
	if (thread_info)
	{
		thread_info->push_msg(bev, msg);
	}



}

void Server::socket_read_cb(bufferevent *bev, void *arg)
{
	char msg[4096];

	size_t len = bufferevent_read(bev, msg, sizeof(msg) - 1);

	msg[len] = '\0';
	//printf("server read the data %s\n", msg);

	Server* server = (Server*)arg;
	server->handle_input(bev, msg, len);
}

void Server::socket_event_cb(bufferevent *bev, short events, void *arg)
{
	if (events & BEV_EVENT_EOF)
	{
		printf("connection closed\n");

		Server* server = (Server*)arg;
		server->handle_close(bev);
	}
	else if (events & BEV_EVENT_ERROR)
	{
		printf("some other error\n");
	}

	//这将自动close套接字和free读写缓冲区  
	bufferevent_free(bev);
}

void Server::run()
{
	event_base_dispatch(m_base);
}

void Server::handle_close(bufferevent *bev)
{
	int fd = bufferevent_getfd(bev);
	auto iter = m_client_list.find(fd);
	if (iter != m_client_list.end())
	{
		m_client_list.erase(iter);
	}
}


void Server::handle_accept(evutil_socket_t fd, sockaddr *address, int socklen)
{
	auto iter = m_client_list.find(fd);
	if (iter != m_client_list.end())
	{
		return;
	}

	//bufferevent* new_bev = bufferevent_socket_new(m_base, fd, BEV_OPT_CLOSE_ON_FREE);	//单线程版本
	bufferevent* new_bev = bufferevent_socket_new(m_base, fd, BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE);	//多线程版本

	bufferevent_setcb(new_bev, Server::socket_read_cb, NULL, Server::socket_event_cb, this);
	bufferevent_enable(new_bev, EV_READ | EV_PERSIST);

	ClientConnection* new_client = new ClientConnection(new_bev);
	new_client->init(fd, address, socklen);
	m_client_list[fd] = new_client;

	//new_client->send_msg("hello client");


	//char reply[] = "hello client";
	//bufferevent_write(new_bev, reply, strlen(reply));
}

void Server::handle_timer(int fd, short event)
{
	cout << "Server::handle_timer tid: 【" << std::this_thread::get_id() << "】" << endl;

	for each(auto iter in m_client_list)
	{
		char reply[] = "hello client";

		//(iter).second->send_msg("hello client timer");
	}

	m_thread_mgr->handle_timer(fd, event);
}
