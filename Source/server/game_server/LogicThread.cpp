#include "LogicThread.h"
#include "ThreadMsg.h"
#include <event2/bufferevent.h>
#include <iostream>
#include <thread>
#include <sstream>
#include <event2/event.h>

void thread_task(void* args) 
{
	LogicThread* logic_thread = (LogicThread*)args;

	logic_thread->init();
	logic_thread->run();
}


LogicThread::LogicThread()
{
	m_thread = std::thread(thread_task, this);
	//std::thread t(thread_task, this);
	//m_thread(std::move(t));
}


LogicThread::~LogicThread()
{
}

void LogicThread::start()
{

}

void LogicThread::push_msg(bufferevent *bev, string msg)
{
	cout <<"push_msg t_id: "<< std::this_thread::get_id() << endl;
	ThreadMsg *t_msg = new ThreadMsg();
	t_msg->set_msg(bev, msg);

	//
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_msg_list.push_back(t_msg);
		m_condition.notify_one();
	}
	
}

ThreadMsg* LogicThread::pop_msg()
{
	//cout << "pop_msg t_id: " << std::this_thread::get_id() << endl;
	std::unique_lock<std::mutex> lock(m_mutex);
	while (m_msg_list.empty())
	{
		m_condition.wait(lock);
	}
	ThreadMsg* msg = m_msg_list.front();
	m_msg_list.pop_front();

	return msg;
}

ThreadMsg* LogicThread::pop_msg1()
{
	//cout << "pop_msg t_id: " << std::this_thread::get_id() << endl;

	ThreadMsg* msg = nullptr;
	std::unique_lock<std::mutex> lock(m_mutex);
	if (false == m_msg_list.empty())
	{
		msg = m_msg_list.front();
		m_msg_list.pop_front();
	}
	

	return msg;
}

void LogicThread::init()
{
//	m_base = event_base_new();
}

void LogicThread::run()
{
	while (1)
	{
//		event_base_dispatch(m_base);

		ThreadMsg* msg = pop_msg();
		if (msg)
		{
			handle_msg(msg);
		}
		//Sleep(1);
	}
	
	
}

void LogicThread::handle_msg(ThreadMsg* msg)
{
	cout << "LogicThread::handle_msg ------------- tid = " << std::this_thread::get_id() << endl;
	bufferevent *bev = (bufferevent*)msg->m_args;
	int fd = bufferevent_getfd(bev);

	//打印收到的信息
	{
		//std::lock_guard<std::mutex> lock(m_mutex);
		//cout << endl << "收到客户端信息: [" << msg->m_msg << "]" << endl;
	}

	stringstream ss;
	ss << msg->m_msg<< " + pong~~~";

	//收到消息后返回给客户端
	bufferevent_write(bev, ss.str().c_str(), ss.str().size());
}

void LogicThread::handle_timer(int fd, short event)
{
	stringstream ss;
	ss << "handle_timer fd";

	cout << "LogicThread::handle_timer tid = " << std::this_thread::get_id() << endl;

	//收到消息后返回给客户端
	//bufferevent_write(bev, ss.str().c_str(), ss.str().size());
}
