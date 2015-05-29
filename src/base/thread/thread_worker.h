#ifndef _THREAD_WORKER_H_
#define _THREAD_WORKER_H_

#include "public.h"
#include "thread/thread_task.h"
#include "utility/share_ptr.h"


namespace Thread
{

class ThreadTask;

class ThreadWorker : public RefCounter
{
	friend void* ThreadWorkerFunc( void* param );
public:
	ThreadWorker();
	~ThreadWorker();
	
	bool Init();

	void DoOnce();
	
	bool Busy() const;

	ThreadHandle& Key();
	
	ThreadCond& Condition();

	void Join( ThreadTaskPtr task );
		
private:
	ThreadHandle			m_handle;
	ThreadCond				m_t_cond;
	ThreadMutex				m_t_mutex;
	
	volatile mutable bool	m_busy;
	
	ThreadTaskPtr			m_task;
};

typedef SharePtr<ThreadWorker> ThreadWorkerPtr;

}// End of Thread

#endif//_THREAD_WORKER_H_
