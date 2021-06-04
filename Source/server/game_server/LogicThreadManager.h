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

	void handle_timer(int fd, short event);

	LogicThread* get_thread(int thread_id);

private:
	vector<LogicThread*>		m_thread_list;
	LogicThread*			m_thread = nullptr;
};

