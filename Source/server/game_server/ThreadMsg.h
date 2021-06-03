#pragma once

#include <string>

using namespace std;

//线程间的消息
class ThreadMsg
{
public:
	ThreadMsg();
	~ThreadMsg();


	string	m_msg;
};

