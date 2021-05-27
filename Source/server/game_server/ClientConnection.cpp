#include "ClientConnection.h"



ClientConnection::ClientConnection()
{
}


ClientConnection::~ClientConnection()
{
}

void ClientConnection::init(int fd, struct sockaddr *address, int socklen)
{
	m_fd = fd;
	memcpy(&m_addr, address, socklen);
}
