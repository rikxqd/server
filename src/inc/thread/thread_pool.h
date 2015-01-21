#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <vector>
#include <queue>

#include "public.h"
#include "singleton/singleton.h"
#include "thread_task.h"


class ThreadWorker;
class ThreadTask;

class ThreadPool
{
	friend class ThreadWorker;
	friend void* PoolMainThreadFunc( void* param );
public:
	ThreadPool();
	explicit ThreadPool( uint32 min, uint32 max );
	~ThreadPool();

	bool Init();
	
	bool Running() const;
	
	void Recovery();

	void Join( TaskHandle handle, TaskParam* param );

protected:
	ThreadWorker* Dispath();
	
	ThreadWorker* Done( ThreadWorker* worker );

private:
	pthread_t		m_t_tid;
	pthread_mutex_t	m_t_mutex;
	
	bool	m_running;
	uint32	m_min_count;
	uint32	m_cur_count;
	uint32	m_max_count;

	std::vector< ThreadWorker* >	m_workers;
	std::queue< ThreadWorker* >		m_idles;
	std::queue< ThreadTask >		m_waitting_tasks;
};

#endif//_THREAD_POOL_H_
