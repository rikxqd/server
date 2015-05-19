#include "thread_pool.h"

#include <unistd.h>

#include "thread/thread_worker.h"
#include "thread/thread_task.h"
#include "thread/thread_lock.h"
#include "thread/thread_func.h"
#include "global.h"


namespace Thread
{

void* PoolMasterThreadFunc( void* param );

ThreadPool::ThreadPool()
    : m_running( false )
    , m_count( 2 )
{
	Thread::API::MutexInit( &m_lock );
}

ThreadPool::ThreadPool( uint32 count )
	: m_running( false )
	, m_count( count )
{
	Thread::API::MutexInit( &m_lock );
}

ThreadPool::~ThreadPool()
{
	Stop();
}

void ThreadPool::Start()
{
    for ( auto worker : m_workers )
        DELETE_VALUE( worker );
    m_workers.clear();
 
    int32 ret = Thread::API::ThreadCreate( &m_handle, NULL, PoolMasterThreadFunc, this );
    if ( 0 != ret )
		return;
    
	m_running = true;

    for ( uint32 i = 0 ; i < m_count ; ++i )
    {
        ThreadWorker* worker = new ThreadWorker();
        if ( worker->Init( this ) )
            m_workers.push_back( worker );
        else
            DELETE_VALUE( worker );
    }

	for ( ; m_workers.size() != m_idles.size() ; ) 
		Time::SleepMsec( 100 );
}

void ThreadPool::Stop()
{
	if ( m_running )
	{
		m_running = false;
		Thread::API::ThreadJoin( m_handle, NULL );
		g_log.Info( "Stop ThreadPool" );
	}
}

bool ThreadPool::Running() const
{
    return (m_running || !m_waitting_tasks.empty());
}

void ThreadPool::Join( ThreadTaskPtr task )
{
	if ( !m_running )
		return;

    m_waitting_tasks.push( task );
    Dispath();
}

void ThreadPool::Dispath()
{
    if ( m_idles.empty() || m_waitting_tasks.empty() )
        return;
    
	
	ThreadWorker* worker = NULL;
	ThreadTaskPtr task;

	{
		GuardLock lock( &m_lock );
		worker = m_idles.front();
		m_idles.pop();

		task = m_waitting_tasks.front();
		m_waitting_tasks.pop();
	}

	if ( worker )
	{
		worker->Join( task );

		if ( !worker->Busy() )
			Thread::API::ThreadCondSignal( &worker->Condition() );
	}
}

bool ThreadPool::Done( ThreadWorker* worker )
{
	if ( m_waitting_tasks.empty() )
	{
		GuardLock lock( &m_lock );
		m_idles.push( worker );
		return false;
	}

	GuardLock lock( &m_lock );
	ThreadTaskPtr task = m_waitting_tasks.front();
	m_waitting_tasks.pop();
	worker->Join( task );
	
	return true;
}

void ThreadPool::Recovery()
{
	g_log.Info( "Recovery ThreadPool" );
	for ( auto worker : m_workers )
	{
		g_log.Info( "Recovery ...." );
		if ( !worker->Busy() )
			Thread::API::ThreadCondSignal( &worker->Condition() );

		Thread::API::ThreadJoin( worker->Key(), NULL );
	}

	for ( auto worker : m_workers )
		DELETE_VALUE( worker );
	m_workers.clear();
}

void* PoolMasterThreadFunc( void* param )
{
	ThreadPool* pool = static_cast< ThreadPool* >( param );
	if ( !pool )
		return NULL;
    
	while ( pool->Running() )
	{
		Time::SleepMsec( 200 );
	}

	pool->Recovery();
    
	return NULL;
}

}// End of Thread
