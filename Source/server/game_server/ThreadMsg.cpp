#include "ThreadMsg.h"



ThreadMsg::ThreadMsg()
{
}


ThreadMsg::~ThreadMsg()
{
}

void ThreadMsg::set_msg(void *args, string msg)
{
	m_args = args;
	m_msg = msg;
}
