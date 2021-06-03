#pragma once

#include <vector>

using namespace std;


class LogicThread;


class LogicThreadManager
{
public:
	LogicThreadManager();
	~LogicThreadManager();


	void init(int threadNum);

	LogicThread* get_thread(int thread_id);


	vector<LogicThread*>		m_thread_list;
};

