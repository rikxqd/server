#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include <list>

#include "public.h"
#include "singleton/singleton.h"
#include "thread/thread_task.h"
#include "thread/thread_pool.h"
#include "time/timer.h"


class Timer;

class TimerManager : NonCopyable, public Thread::ThreadTask, public Singleton< TimerManager >
{
	friend class Singleton< TimerManager >;
	TimerManager();
public:
	~TimerManager();

	 void AddTimer( TimerPtr timer );
	 void RemoveTimer( TimerPtr timer );

	 void Start( Thread::ThreadPoolPtr pool = NULL );
	 void Stop();

protected:
	void Tick();

	virtual void Process();

private:
	volatile mutable bool	m_running;
	uint32					m_delay;
	ThreadMutex				m_lock;
	std::list< TimerPtr >	m_list;
};

#endif//_TIMER_MANAGER_H_
