#include "thread_pool.h"

#include <unistd.h>

#include "thread/thread_worker.h"
#include "global.h"


void* PoolMainThreadFunc( void* param );

ThreadPool::ThreadPool()
    : m_running( false )
    , m_min_count( 2 )
    , m_cur_count( 2 )
    , m_max_count( 2 )
{
}

ThreadPool::ThreadPool( uint32 min, uint32 max )
{
    if ( min > max )
        min = max;
    
    m_min_count = min;
    m_cur_count = min;
    m_max_count = max;
}

ThreadPool::~ThreadPool()
{
}

bool ThreadPool::Init()
{
    for ( auto worker : m_workers )
        DELETE_VALUE( worker );
    m_workers.clear();
    
    pthread_mutex_init( &m_t_mutex, NULL );
 
    int32 ret = pthread_create( &m_t_tid, NULL, PoolMainThreadFunc, this );
    if ( 0 != ret )
        return false;
    
    for ( uint32 i = 0 ; i < m_cur_count ; ++i )
    {
        ThreadWorker* worker = new ThreadWorker();
        if ( worker->Init( this ) )
            m_workers.push_back( worker );
        else
            DELETE_VALUE( worker );
    }
    
    return true;
}

void ThreadPool::Stop()
{
	m_running = false;
	pthread_join( m_t_tid, NULL );
	g_log.Debug( "Stop Master" );
}

bool ThreadPool::Running() const
{
    return m_running;
}

void ThreadPool::Join( TaskHandle handle, void* param )
{
    ThreadTask task( handle, param );
    m_waitting_tasks.push( task );
    Dispath();
}

bool ThreadPool::TaskEmpty() const
{
	return m_idles.empty();
}

ThreadWorker* ThreadPool::Dispath()
{
    if ( m_idles.empty() || m_waitting_tasks.empty() )
        return NULL;
    
	pthread_mutex_lock( &m_t_mutex );
	ThreadWorker* worker = m_idles.front();
	m_idles.pop();

	ThreadTask task = m_waitting_tasks.front();
	m_waitting_tasks.pop();
	pthread_mutex_unlock( &m_t_mutex );

    worker->Join( task );
    
    if ( !worker->Busy() )
	    pthread_cond_signal( &worker->ThreadCond() );
	    
	return worker;
}

ThreadWorker* ThreadPool::Done( ThreadWorker* worker )
{
	{
		pthread_mutex_lock( &m_t_mutex );
		m_idles.push( worker );
		pthread_mutex_unlock( &m_t_mutex );
	}
	
	return Dispath();
}

void ThreadPool::Recovery()
{
	for ( auto worker : m_workers )
	{
		pthread_join( worker->Key(), NULL );
		g_log.Debug( "Stop Worker %lu",  worker->Key() );
	}
}

void* PoolMainThreadFunc( void* param )
{
	ThreadPool* pool = static_cast< ThreadPool* >( param );
	if ( !pool )
		return NULL;
    
	pool->m_running = true;
	while ( pool->Running() )
	{

		sleep( 3 );
	}

	pool->Recovery();
    
	return NULL;
}
