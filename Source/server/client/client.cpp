
#include "client.h"

#include <iostream>

#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<errno.h>  
#include<unistd.h>  

#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  

#include<event.h>  
#include<event2/bufferevent.h>  
#include<event2/buffer.h>  
#include<event2/util.h>  

using namespace std;


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

void Client::init(std::string& ip, int port, int client_id)
{
	cout<<"Client::init ip:["<<ip<<"]"<<endl;
	cout<<"Client::init port:["<<port<<"]"<<endl;
	cout<<"Client::init client_id:["<<client_id<<"]"<<endl;
	m_ip = ip;
	m_port = port;
	m_client_id = client_id;

	event_base* m_base = event_base_new();
	if(NULL == m_base)
	{
		cout<<"Client::init m_base = "<<m_base<<endl;
	}

	m_bev = bufferevent_socket_new(m_base, -1, BEV_OPT_CLOSE_ON_FREE);

	m_ev_cmd = event_new(m_base, STDIN_FILENO, EV_READ | EV_PERSIST, cmd_msg_cb, (void*)this);

	event_add(m_ev_cmd, NULL);

	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = (m_port);
	inet_aton(m_ip.c_str(), &server_addr.sin_addr);

	bufferevent_socket_connect(m_bev, (sockaddr*)&server_addr, sizeof(server_addr));

	bufferevent_setcb(m_bev, server_msg_cb, NULL, event_cb, (void*)this);
	bufferevent_enable(m_bev, EV_READ | EV_PERSIST);

	event_base_dispatch(m_base);
}

int Client::tcp_connect_server(std::string server_ip, int port)
{
	return 0;
}

void Client::cmd_msg_cb(int fd, short events, void* args)
{
	char msg[1024] = {0};

	int ret = read(fd, msg, sizeof(msg));
	if(ret < 0)
	{
		cout<<"cmd_msg_cb read error"<<endl;
		return;
	}

	cout<<"cmd_msg_cb msg: "<<msg<<endl;

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
	CommonMsg* common_msg = (CommonMsg*)msg;

	cout<<"Client::hand_input common_msg->id: "<<common_msg->id<<endl;
	cout<<"Client::hand_input common_msg->type: "<<common_msg->type<<endl;
	cout<<"Client::hand_input common_msg->sub_type: "<<common_msg->sub_type<<endl;
}

void Client::event_cb(bufferevent* bev, short events, void* args)
{
	if(events & BEV_EVENT_EOF)
	{
		cout<<"connection closed "<<endl;
	}
	else if(events & BEV_EVENT_ERROR)
	{
		cout<<"some other error events = "<<events<<endl;
	}
	else if(events & BEV_EVENT_CONNECTED)
	{
		cout<<"client has connected to server "<<endl;
		return;
	}

	bufferevent_free(bev);

	event* ev = (event*)args;
	event_free(ev);
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