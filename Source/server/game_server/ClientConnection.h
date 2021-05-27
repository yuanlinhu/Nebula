#pragma once

#include <WinSock2.h>

class ClientConnection
{
public:
	ClientConnection();
	~ClientConnection();

	void init(int fd, struct sockaddr *address, int socklen);


private:
	int m_fd = 0;
	sockaddr m_addr;
};

