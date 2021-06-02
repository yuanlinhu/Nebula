#pragma once

#include <WinSock2.h>
#include <string>
#include <event2/bufferevent.h>

using namespace std;

struct bufferevent;

class ClientConnection
{
public:
	explicit ClientConnection(bufferevent* new_bev);
	~ClientConnection();

	void init(int fd, struct sockaddr *address, int socklen);
	void send_msg(const void *data, size_t size);
	void send_msg(string str);

private:
	int m_fd = 0;
	sockaddr m_addr;

	bufferevent* m_buffer_event = nullptr;
};

