#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <vector>
#include <queue>
#include "public.h"
#include "singleton/singleton.h"
#include "thread/thread_task.h"
#include "thread/thread_worker.h"


namespace Thread
{

class ThreadWorker;

class ThreadPool : public Singleton<ThreadPool>
{
	friend class Singleton<ThreadPool>;
	friend class ThreadWorker;
	friend void* MasterThreadPoolFunc( void* param );
	ThreadPool();
public:
	~ThreadPool();

	ThreadHandle Key() const;

	void Start( uint32 count = 0 );

	void Stop();
	
	bool Running() const;

	void Join( ThreadTaskPtr task );

protected:
	void Dispath();
	
	bool Done( ThreadWorkerPtr worker );

	void Recovery();

private:
	ThreadHandle					m_handle;
	ThreadMutex						m_lock;
	
	volatile mutable bool			m_running;
	uint32							m_count;

	std::vector< ThreadWorkerPtr >	m_workers;
	std::queue< ThreadWorkerPtr >	m_idles;
	std::queue< ThreadTaskPtr >		m_waitting_tasks;
};

}// End of Thread

#endif//_THREAD_POOL_H_
