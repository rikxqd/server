#ifndef _THREAD_WORKER_H_
#define _THREAD_WORKER_H_

#include "public.h"
#include "singleton/singleton.h"
#include "thread/thread_task.h"


class ThreadPool;
class ThreadTask;

class ThreadWorker
{
	friend void* PoolThreadFunc( void* param );
public:
	ThreadWorker();
	~ThreadWorker();
	
	bool Init( ThreadPool* pool );
	
	bool Busy() const;

	pthread_t& Key();
	
	pthread_cond_t& ThreadCond();

	ThreadPool* Owner();

	void Join( ThreadTask& task );

protected:
	void Start();
	
private:
	pthread_t		m_t_tid;
	pthread_cond_t	m_t_cond;
	pthread_mutex_t	m_t_mutex;
	
	bool			m_busy;
	
	ThreadTask		m_task;
	ThreadPool*		m_owner;
};

#endif//_THREAD_WORKER_H_
