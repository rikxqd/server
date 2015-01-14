#ifndef _THREAD_WORKER_H_
#define _THREAD_WORKER_H_

#include "public.h"
#include "singleton/singleton.h"
#include "thread/thread_job.h"


class ThreadPool;
class ThreadJob;

class ThreadWorker
{
public:
	ThreadWorker();
	~ThreadWorker();
	
	bool Init( ThreadPool* pool );
	
	bool Busy() const;
	
	pthread_cond_t& ThreadCond();

	ThreadPool* Owner();

	void Jion( ThreadJob* job );

	void Start();
	
private:
	pthread_t		m_t_tid;
	pthread_cond_t	m_t_cond;
	pthread_mutex_t	m_t_mutex;
	
	bool			m_busy;
	
	ThreadJob*		m_job;
	ThreadPool*		m_owner;
};

#endif//_THREAD_WORKER_H_
