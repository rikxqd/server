#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include <list>

#include "public.h"
#include "singleton/singleton.h"
#include "thread/thread_task.h"


class Timer;

class TimerManager : public Thread::ThreadTask, public Singleton< TimerManager >
{
	friend class Singleton< TimerManager >;
	TimerManager();
public:
	~TimerManager();

	 void AddTimer( Timer* timer );
	 void RemoveTimer( Timer* timer );

	 void Start();
	 void Stop();

protected:
	void Tick();

	virtual void Process();

private:
	bool				m_start;
	uint32				m_delay;
	ThreadMutex		m_t_mutex;
	std::list< Timer* >	m_list;
};

#endif//_TIMER_MANAGER_H_
