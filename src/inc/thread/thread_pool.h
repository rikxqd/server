#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <vector>
#include <queue>

#include "public.h"
#include "singleton/singleton.h"
#include "thread_task.h"


class ThreadWorker;
class ThreadTask;

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

	void Join( TaskHandle handle, void* param );

protected:
	ThreadWorker* Dispath();
	
	ThreadWorker* Done( ThreadWorker* worker );

	void Recovery();

private:
	pthread_t			m_t_tid;
	pthread_mutex_t	m_t_mutex;
	
	bool	m_running;
	uint32	m_count;

	std::vector< ThreadWorker* >	m_workers;
	std::queue< ThreadWorker* >	m_idles;
	std::queue< ThreadTask >		m_waitting_tasks;
};

#endif//_THREAD_POOL_H_
