#include "LogicThread.h"
#include "ThreadMsg.h"


LogicThread::LogicThread()
{
}


LogicThread::~LogicThread()
{
}

void LogicThread::start()
{

}

void LogicThread::push_msg(bufferevent *bev, string msg)
{
	ThreadMsg *t_msg = new ThreadMsg();
	t_msg->set_msg(bev, msg);

	//
	{
		std::lock_guard<std::mutex> lck(m_mutex);
		m_msg_list.push_back(t_msg);
		m_condition.notify_all();
	}
	
}

