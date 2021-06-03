#pragma once

#include <thread>
#include <list>

using namespace std;


class ThreadMsg;

class LogicThread
{
public:
	LogicThread();
	~LogicThread();


	void start();

	void push_msg(string msg);
	void pop_msg(string msg);


private:
	std::thread m_thread;

	list<ThreadMsg*>	m_in_msg_list;
	list<ThreadMsg*>	m_out_msg_list;
};

