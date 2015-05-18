#include "thread_pool.h"

#include <unistd.h>

#include "thread/thread_worker.h"
#include "thread/thread_task.h"
#include "thread/thread_lock.h"
#include "global.h"


void* PoolMasterThreadFunc( void* param );


ThreadPool::ThreadPool()
    : m_running( false )
    , m_count( 10 )
{
}

ThreadPool::ThreadPool( uint32 count )
	: m_running( false )
	, m_count( count )
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::Start()
{
    for ( auto worker : m_workers )
        DELETE_VALUE( worker );
    m_workers.clear();
    
    pthread_mutex_init( &m_t_mutex, NULL );
 
    int32 ret = pthread_create( &m_t_tid, NULL, PoolMasterThreadFunc, this );
    if ( 0 != ret )
	{
        g_log.Fatal( "Master fatal" );
		return;
	}
    
	m_running = true;

    for ( uint32 i = 0 ; i < m_count ; ++i )
    {
        ThreadWorker* worker = new ThreadWorker();
        if ( worker->Init( this ) )
            m_workers.push_back( worker );
        else
            DELETE_VALUE( worker );
    }

	while ( m_workers.size() != m_idles.size() ) {}
}

void ThreadPool::Stop()
{
	if ( m_running )
	{
		m_running = false;
		pthread_join( m_t_tid, NULL );
		g_log.Info( "Stop ThreadPool" );
	}
}

bool ThreadPool::Running() const
{
    return (m_running || !m_waitting_tasks.empty());
}

void ThreadPool::Join( ThreadTask* task )
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
    
	pthread_mutex_lock( &m_t_mutex );
	ThreadWorker* worker = m_idles.front();
	m_idles.pop();
	
	ThreadTask* task = m_waitting_tasks.front();
	m_waitting_tasks.pop();
	pthread_mutex_unlock( &m_t_mutex );

    worker->Join( task );
    
    if ( !worker->Busy() )
	    pthread_cond_signal( &worker->ThreadCond() );
}

bool ThreadPool::Done( ThreadWorker* worker )
{
	if ( m_waitting_tasks.empty() )
	{
		ThreadLock lock( m_t_mutex );
		m_idles.push( worker );
		return false;
	}

	ThreadLock lock( m_t_mutex );
	ThreadTask* task = m_waitting_tasks.front();
	m_waitting_tasks.pop();
	worker->Join( task );
	
	return true;
}

void ThreadPool::Recovery()
{
	g_log.Info( "Recovery ThreadPool" );
	for ( auto worker : m_workers )
		pthread_join( worker->Key(), NULL );
}

void* PoolMasterThreadFunc( void* param )
{
	ThreadPool* pool = static_cast< ThreadPool* >( param );
	if ( !pool )
		return NULL;
    
	while ( pool->Running() )
	{

		Time::SleepMsec( 2 * 1000 );
	}

	pool->Recovery();
    
	return NULL;
}
