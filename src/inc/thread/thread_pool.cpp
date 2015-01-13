#include "thread_pool.h"
#include <unistd.h>


static void* PoolMainThreadFunc( void* param );
static void* PoolThreadFunc( void* param );

ThreadPool::ThreadPool()
    : m_run( false )
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
    m_run = true;
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

bool ThreadPool::Run() const
{
    return m_run;
}

void ThreadPool::Destroy()
{
    
}

void* PoolMainThreadFunc( void* param )
{
    ThreadPool* pool = static_cast< ThreadPool* >( param );
    if ( !pool )
        return NULL;
    
    while ( pool->Run() )
    {

        sleep( 3 );
    }
    
    return NULL;
}

void* PoolThreadFunc( void* param )
{
    ThreadWorker* worker = static_cast< ThreadWorker* >( param );
    if ( !worker )
        return NULL;
        
    
}