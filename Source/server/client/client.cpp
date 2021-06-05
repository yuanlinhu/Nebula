
#include "client.h"

#include <iostream>
#include <Ws2tcpip.h>

//#include<sys/types.h>  
 
#include<errno.h>  


#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  

#include<event.h>  
#include<event2/bufferevent.h>  
#include<event2/buffer.h>  
#include<event2/util.h>  
#include <event2/thread.h>

#include <iostream>
#include <sstream>

using namespace std;


static int index = 0;

struct CommonMsg
{
    int id;
    int type;
    int sub_type;

};

Client::Client()
:m_base(NULL)
,m_port(0)
,m_client_id(0)
,m_bev(NULL)
{

}

void Client::init_command()
{
	//intptr_t h = (intptr_t)GetConsoleWindow();
	//m_ev_cmd = event_new(m_base, h, EV_READ | EV_PERSIST, cmd_msg_cb, (void*)this);

	//_fileno(stdin);
	//m_ev_cmd = event_new(m_base, _fileno(stdin), EV_READ | EV_PERSIST, cmd_msg_cb, (void*)this);
	//event_add(m_ev_cmd, NULL);
}

void Client::init(std::string ip, int port, int client_id)
{

	WORD sockVersion = MAKEWORD(2, 2);         //请求2.2版本的WinSock库
											   // 用于接收Wjndows Socket的结构信息
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return;
	}

	//evthread_use_windows_threads();

	cout<<"Client::init ip:["<<ip<<"]"<<endl;
	cout<<"Client::init port:["<<port<<"]"<<endl;
	cout<<"Client::init client_id:["<<client_id<<"]"<<endl;
	m_ip = ip;
	m_port = port;
	m_client_id = client_id;

	m_base = event_base_new();
	if(NULL == m_base)
	{
		cout<<"Client::init m_base = "<<m_base<<endl;
	}

	m_bev = bufferevent_socket_new(m_base, -1, BEV_OPT_CLOSE_ON_FREE);



	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(m_port);
	inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

	//int sock_fd = 0;
	m_sock_fd = bufferevent_socket_connect(m_bev, (sockaddr*)&server_addr, sizeof(server_addr));


	bufferevent_setcb(m_bev, server_msg_cb, NULL, event_cb, (void*)this);
	bufferevent_enable(m_bev, EV_READ | EV_PERSIST);



	
}

void Client::run()
{
	event_base_dispatch(m_base);
}

//int Client::tcp_connect_server(std::string server_ip, int port)
//{
//	return 0;
//}

void Client::cmd_msg_cb(int fd, short events, void* args)
{
	char msg[1024] = {0};

	int ret = ::recv(fd, msg, sizeof(msg), 0);
	if(ret < 0)
	{
		cout<<"cmd_msg_cb read error"<<endl;
		return;
	}

	//cout<<"cmd_msg_cb msg: "<<msg<<endl;

	Client* client = (Client*)args;
	bufferevent* bev = client->get_bev();



    CommonMsg newMsg;
    newMsg.id = client->get_client_id();
    newMsg.type = client->get_port();
    newMsg.sub_type = 1;

	bufferevent_write(bev, &newMsg, sizeof(newMsg));
	
}

void Client::server_msg_cb(bufferevent* bev, void* args)
{
	char msg[1024] = {0};

	int len = bufferevent_read(bev, msg, sizeof(msg));

	Client* client = (Client*)args;
	client->hand_input(msg, len);
}

void Client::hand_input(void* msg, int len)
{
	//CommonMsg* common_msg = (CommonMsg*)msg;


	//cout<<"Client::hand_input common_msg->id: "<<common_msg->id<<endl;
	//cout<<"Client::hand_input common_msg->type: "<<common_msg->type<<endl;
	//cout<<"Client::hand_input common_msg->sub_type: "<<common_msg->sub_type<<endl;
	if (index % 10 == 0)
	{
		string str((char*)msg, len);
		cout << "收到信息:[" << str << "]" << endl;
	}
}

void Client::test()
{
	Client client;
	client.init("192.168.1.71", 11111,1);
	client.init_timer();
	//client.init_command();
	client.run();
}

void on_timer_cb(int fd, short event, void *arg)
{
	Client* client = (Client*)arg;
	client->handle_timer(fd, event);
}

void Client::handle_timer(int fd, short event)
{
	//cout << "handle_timer fd: 【" << fd << "】" << endl;
	
	stringstream ss;
	index++;
	ss << "hello server ping id: " << index;
	send_msg(ss.str());
}

void Client::send_msg(string str)
{
	bufferevent_write(m_bev, str.c_str(), str.size());
}

void Client::init_timer()
{
	timeval tv;

	tv.tv_sec = 2;
	tv.tv_usec = 0;
	//m_event_timer = evtimer_new(m_base, on_timer_cb, this);
	m_event_timer = event_new(m_base, -1, EV_PERSIST, on_timer_cb, this);
	evtimer_add(m_event_timer, &tv);
}


void Client::event_cb(bufferevent* bev, short events, void* args)
{
	int error = WSAGetLastError();
	if(events & BEV_EVENT_EOF)
	{
		cout<<"connection closed "<<endl;
	}
	else if(events & BEV_EVENT_ERROR)
	{
		cout<<"some other error events = "<<events<<endl;
		return;
	}
	else if(events & BEV_EVENT_CONNECTED)
	{
		cout<<"client has connected to server "<<endl;
		return;
	}

	bufferevent_free(bev);

	//Client* ev = (Client*)args;
	//event_free(ev);
	return;
}

bufferevent* Client::get_bev()
{
	return m_bev;
}

int Client::get_port()
{
	return m_port;
}

int Client::get_client_id()
{
	return m_client_id;
}