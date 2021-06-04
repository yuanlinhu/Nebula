#include "LogicThreadManager.h"
#include "LogicThread.h"


LogicThreadManager::LogicThreadManager()
{
}


LogicThreadManager::~LogicThreadManager()
{
}

void LogicThreadManager::init(int threadNum)
{
	if (threadNum <= 0)
	{
		threadNum = 1;
	}

	m_thread = new LogicThread();

	//for (int i = 0; i < threadNum; ++i)
	//{
	//	LogicThread* newThead = new LogicThread();
	//	m_thread_list.push_back(newThead);
	//}
}

void LogicThreadManager::handle_timer(int fd, short event)
{
	m_thread->handle_timer(fd, event);
}

LogicThread* LogicThreadManager::get_thread(int thread_id)
{
	return m_thread;
	//暂时只有一个线程
	//return m_thread_list[0];
}

