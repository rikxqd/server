#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include <list>

#include "singleton/singleton.h"
#include "thread/thread_task.h"
#include "public.h"


class Timer;

class TimerManager : public ThreadTask, public Singleton< TimerManager >
{
	friend class Singleton< TimerManager >;
	friend void TimerManagerFunc( void *param );

	TimerManager();
public:
	~TimerManager();

	 void AddTimer( Timer* timer );
	 void RemoveTimer( Timer* timer );

	 void Start();
	 void Stop();

protected:
	void Tick();

	virtual void Do();

private:
	bool				m_start;
	uint32				m_delay;
	pthread_mutex_t		m_t_mutex;
	std::list< Timer* >	m_list;
};

#endif//_TIMER_MANAGER_H_
