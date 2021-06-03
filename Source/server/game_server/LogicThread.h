#pragma once

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>

using namespace std;

struct bufferevent;
class ThreadMsg;

class LogicThread
{
public:
	LogicThread();
	~LogicThread();


	void start();

	void push_msg(bufferevent *bev, string msg);


private:
	std::mutex		m_mutex;
	std::condition_variable m_condition;
	std::thread		m_thread;

	list<ThreadMsg*>	m_msg_list;
};

