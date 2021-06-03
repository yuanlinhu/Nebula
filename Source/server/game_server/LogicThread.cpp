#include "LogicThread.h"
#include "ThreadMsg.h"
#include <event2/bufferevent.h>
#include <iostream>
#include <thread>


void thread_task(void* args) 
{
	LogicThread* logic_thread = (LogicThread*)args;

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
	cout << "pop_msg t_id: " << std::this_thread::get_id() << endl;
	std::unique_lock<std::mutex> lock(m_mutex);
	while (m_msg_list.empty())
	{
		m_condition.wait(lock);
	}
	ThreadMsg* msg = m_msg_list.front();
	m_msg_list.pop_front();

	return msg;
}

void LogicThread::run()
{
	ThreadMsg* msg = pop_msg();
	if (msg)
	{
		handle_msg(msg);
	}
	
}

void LogicThread::handle_msg(ThreadMsg* msg)
{

	bufferevent *bev = (bufferevent*)msg->m_args;
	int fd = bufferevent_getfd(bev);

	//打印收到的信息
	{
		//std::lock_guard<std::mutex> lock(m_mutex);
		cout << endl << "收到客户端信息: [" << msg->m_msg << "]" << endl;
	}

	//收到消息后返回给客户端
	char reply[] = "hello client pong";
	bufferevent_write(bev, reply, strlen(reply));
}
