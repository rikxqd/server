#include "thread_pool.h"

#include <unistd.h>

#include "thread/thread_worker.h"


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
    m_running = true;
    int32 ret = pthread_create( &m_t_tid, NULL, PoolMainThreadFunc, this );
    if ( 0 != ret )
        return false;
    
    for ( uint32 i = 0 ; i < m_cur_count ; ++i )
    {
        ThreadWorker* worker = new ThreadWorker();
        if ( worker->Init( this ) )
        {
            m_workers.push_back( worker );
            m_idles.push( worker );
        }
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

void ThreadPool::Jion( ThreadJob* job )
{
    m_waitting_jobs.push( job );
    Dispath();
}

void ThreadPool::Jion( JobHandle handle, JobParam* param )
{
    ThreadJob job;
    job.Set( handle, param );
    m_waitting_jobs.push( &job );
    Dispath();
}

bool ThreadPool::Dispath()
{
    if ( m_idles.empty() || m_waitting_jobs.empty() )
        return false;
        
    ThreadWorker* worker = m_idles.front();
    m_idles.pop();

    ThreadJob* job = m_waitting_jobs.front();
    m_waitting_jobs.pop();
    
    worker->Jion( job );
    
    if ( !worker->Busy() )
	    pthread_cond_signal( &worker->ThreadCond() );
	    
	return true;
}

bool ThreadPool::Done( ThreadWorker* worker )
{
	m_idles.push( worker );
	return Dispath();
	//cout << "done" << m_idles.size() << endl;
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
