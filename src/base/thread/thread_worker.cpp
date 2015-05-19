#include "thread_worker.h"

#include "global.h"
#include "thread/thread_pool.h"
#include "thread/thread_lock.h"
#include "thread/thread_func.h"
#include "process/process.h"


namespace Thread
{

void* PoolThreadFunc( void* param );

ThreadWorker::ThreadWorker()
	: m_busy( true )
	, m_owner( NULL )
{
}

ThreadWorker::~ThreadWorker()
{
}

bool ThreadWorker::Init( ThreadPool* pool )
{
    m_owner = pool;
    Thread::API::ThreadCondInit( &m_t_cond, NULL );
    Thread::API::MutexInit( &m_t_mutex, NULL );
    
    return (0 == Thread::API::ThreadCreate( &m_handle, NULL, PoolThreadFunc, this ));
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

ThreadPool* ThreadWorker::Owner()
{
	return m_owner;
}

void ThreadWorker::Join( ThreadTaskPtr task )
{
	m_task = task;
}

void ThreadWorker::Start()
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
	
	m_busy = m_owner->Done( this );
}

void* PoolThreadFunc( void* param )
{
	ThreadWorker* worker = static_cast< ThreadWorker* >( param );
	if ( !worker )
		return NULL;

	g_log.Debug( "Start Worker %d", ProcFunc::ProcId() );

	while ( worker->Owner()->Running() || worker->Busy() )
	{
		worker->Start();
	}

	g_log.Debug( "Stop Worker %d", ProcFunc::ProcId() );
	
	return NULL;
}

}// End of Thread
