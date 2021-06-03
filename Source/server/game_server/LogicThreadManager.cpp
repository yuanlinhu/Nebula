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

	m_thread_list.reserve(threadNum);

	for (int i = 0; i < threadNum; ++i)
	{
		LogicThread* newThead = new LogicThread();
		m_thread_list.push_back(newThead);
	}
}

LogicThread* LogicThreadManager::get_thread(int thread_id)
{
	//暂时只有一个线程
	return m_thread_list[0];
}

