#ifndef _THREAD_WORKER_H_
#define _THREAD_WORKER_H_

#include "singleton/singleton.h"
#include "public.h"


class ThreadPool;

struct ThreadParam 
{
	void *ret; //call in, that is arguments
	void *arg; //call out, that is return value
};
typedef void (*WorkerFunc)( ThreadParam* job );


class ThreadWorker
{
public:
	ThreadWorker();
	~ThreadWorker();
	
	void Init( ThreadPool* pool );
	
	bool Busy() const;
	
	pthread_t& Key();
	pthread_cond_t& ThreadCond();
	pthread_mutex_t& ThreadMutex();

	ThreadPool* Owner();

	void Jion( WorkerFunc func, ThreadParam* param );

	void Start();
	
private:
	pthread_t		m_t_tid;
	pthread_cond_t	m_t_cond;
	pthread_mutex_t	m_t_mutex;
	
	bool			m_busy;
	
	WorkerFunc		m_func;
	ThreadParam*	m_param;
	
	ThreadPool*		m_owner;
};

#endif//_THREAD_WORKER_H_
