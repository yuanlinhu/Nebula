#pragma once

#include <string>


struct bufferevent;

using namespace std;

//�̼߳����Ϣ
class ThreadMsg
{
public:
	ThreadMsg();
	~ThreadMsg();

	void set_msg(void *args, string msg);

	void *m_args = nullptr;
	string	m_msg;
};

