#include "thread_worker.h"

#include "thread/thread_pool.h"
#include "thread/thread_lock.h"
#include "thread/thread_api.h"
#include "process/process.h"


namespace Thread
{

void* ThreadWorkerFunc( void* param );

ThreadWorker::ThreadWorker()
	: m_busy( true )
{
}

ThreadWorker::~ThreadWorker()
{
}

bool ThreadWorker::Init()
{
    Thread::API::ThreadCondInit( &m_t_cond, NULL );
    Thread::API::MutexInit( &m_t_mutex, NULL );
    
    return (0 == Thread::API::ThreadCreate( &m_handle, NULL, ThreadWorkerFunc, this ));
}

void ThreadWorker::DoOnce()
{	
	if ( !m_busy )
	{
		GuardLock lock( &m_t_mutex );
		Thread::API::ThreadCondWait( &m_t_cond, &m_t_mutex );  
	}

	m_busy = true;

	if ( m_task )
	{
		m_task->Process();
		m_task = NULL;
	}

	m_busy = ThreadPool::Instance().Done( this );
}

bool ThreadWorker::Busy() const
{
    return m_busy;
}

ThreadHandle& ThreadWorker::Key()
{
	return m_handle;
}

ThreadCond& ThreadWorker::Condition()
{
	return m_t_cond;
}

void ThreadWorker::Join( ThreadTaskPtr task )
{
	m_task = task;
}


void* ThreadWorkerFunc( void* param )
{
	ThreadWorker* worker = static_cast< ThreadWorker* >( param );
	if ( !worker )
		return NULL;

	DEBUG( "Start Worker %d", Process::ProcessId() );

	while ( ThreadPool::Instance().Running() || worker->Busy() )
	{
		worker->DoOnce();
	}

	DEBUG( "Stop Worker %d", Process::ProcessId() );
	
	return NULL;
}

}// End of Thread
