#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <vector>
#include <queue>

#include "public.h"
#include "singleton/singleton.h"
#include "thread/thread_task.h"


namespace Thread
{

class ThreadWorker;

class ThreadPool : public Singleton< ThreadPool >
{
	friend class ThreadWorker;
	friend void* PoolMasterThreadFunc( void* param );
	friend class Singleton< ThreadPool >;
public:
	ThreadPool();
	explicit ThreadPool( uint32 count );
	~ThreadPool();

	void Start();

	void Stop();
	
	bool Running() const;

	void Join( ThreadTaskPtr task );

protected:
	void Dispath();
	
	bool Done( ThreadWorker* worker );

	void Recovery();

private:
	ThreadHandle						m_t_tid;
	ThreadMutex						m_t_mutex;
	
	volatile mutable bool				m_running;
	uint32	m_count;

	std::vector< ThreadWorker* >		m_workers;
	std::queue< ThreadWorker* >		m_idles;
	std::queue< ThreadTaskPtr >		m_waitting_tasks;
};

}// End of Thread

#endif//_THREAD_POOL_H_
