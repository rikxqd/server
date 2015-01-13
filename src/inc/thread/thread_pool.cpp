#include "thread_pool.h"
#include <unistd.h>


void* PoolMainThreadFunc( void* param );
void* PoolThreadFunc( void* param );


ThreadPool::ThreadPool()
    : m_running( false )
    , m_min_count( 2 )
    , m_cur_count( 2 )
    , m_max_count( 8 )
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
    m_running = true;
    int32 ret = pthread_create( &m_t_tid, NULL, PoolMainThreadFunc, this );
    if ( 0 != ret )
        return false;
    
    for ( uint32 i = 0 ; i < m_cur_count ; ++i )
    {
        ThreadWorker* worker = new ThreadWorker();
        worker->Init( this );
        
        ret = pthread_create( &worker->Key(), NULL, PoolThreadFunc, worker );
        if ( 0 == ret )
            m_workers.push_back( worker );
        else
            DELETE_VALUE( worker );
    }
    
    return true;
}

bool ThreadPool::Running() const
{
    return m_running;
}

void ThreadPool::Recovery()
{
    
}

bool ThreadPool::Jion( WorkerFunc func, ThreadParam* param )
{
	ThreadWorker* worker = m_idles.front();
	worker->Jion( func, param );
	return true;
}

void ThreadPool::Working( ThreadWorker* worker )
{
	m_idles.pop();
}
void ThreadPool::Done( ThreadWorker* worker )
{
	m_idles.push( worker );
}

void* PoolMainThreadFunc( void* param )
{
    ThreadPool* pool = static_cast< ThreadPool* >( param );
    if ( !pool )
        return NULL;
    
    while ( pool->Running() )
    {

        sleep( 3 );
    }

	pool->Recovery();
    
    return NULL;
}

void* PoolThreadFunc( void* param )
{
    ThreadWorker* worker = static_cast< ThreadWorker* >( param );
    if ( !worker )
        return NULL;
     
	ThreadPool* pool = worker->Owner();
	while ( pool->Running() )
	{
		pthread_mutex_lock( &worker->ThreadMutex() );  
		pthread_cond_wait( &worker->ThreadCond(), &worker->ThreadMutex() );  
		pthread_mutex_unlock( &worker->ThreadMutex() );

		pool->Working( worker );
		worker->Start();
		pool->Done( worker );
	}
}