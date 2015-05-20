#ifndef _THREAD_WORKER_H_
#define _THREAD_WORKER_H_

#include "public.h"
#include "thread/thread_task.h"
#include "utility/share_ptr.h"


namespace Thread
{

class ThreadPool;
class ThreadTask;

class ThreadWorker : public RefCounter
{
	friend void* PoolThreadFunc( void* param );
public:
	ThreadWorker();
	~ThreadWorker();
	
	bool Init( ThreadPool* pool );
	
	bool Busy() const;

	ThreadHandle& Key();
	
	ThreadCond& Condition();

	ThreadPool* Owner();

	void Join( ThreadTaskPtr task );

protected:
	void Start();
	
private:
	ThreadHandle			m_handle;
	ThreadCond				m_t_cond;
	ThreadMutex				m_t_mutex;
	
	volatile mutable bool	m_busy;
	
	ThreadTaskPtr			m_task;
	ThreadPool*				m_owner;
};

typedef SharePtr<ThreadWorker> ThreadWorkerPtr;

}// End of Thread

#endif//_THREAD_WORKER_H_
