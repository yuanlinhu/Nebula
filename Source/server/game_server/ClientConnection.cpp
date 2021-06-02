#include "ClientConnection.h"
#include <event2/bufferevent.h>


ClientConnection::ClientConnection(bufferevent* new_bev)
{
	m_buffer_event = new_bev;
}


ClientConnection::~ClientConnection()
{
}

void ClientConnection::init(int fd, struct sockaddr *address, int socklen)
{
	m_fd = fd;
	memcpy(&m_addr, address, socklen);
}

void ClientConnection::send_msg(const void *data, size_t size)
{
	bufferevent_write(m_buffer_event, data, size);
}


void ClientConnection::send_msg(string str)
{
	bufferevent_write(m_buffer_event, str.c_str(), str.size());
}