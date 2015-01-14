#include "thread_worker.h"

#include "thread_pool.h"


void* PoolThreadFunc( void* param );

ThreadWorker::ThreadWorker()
    : m_busy( false )
    , m_job( NULL )
	, m_owner( NULL )
{
}

ThreadWorker::~ThreadWorker()
{
}

bool ThreadWorker::Init( ThreadPool* pool )
{
    m_owner = pool;
    pthread_cond_init( &m_t_cond, NULL );
    pthread_mutex_init( &m_t_mutex, NULL );
    
    int32 ret = pthread_create( &m_t_tid, NULL, PoolThreadFunc, this );
    return (0 == ret);
}

bool ThreadWorker::Busy() const
{
    return m_busy;
}

pthread_cond_t& ThreadWorker::ThreadCond()
{
	return m_t_cond;
}

ThreadPool* ThreadWorker::Owner()
{
	return m_owner;
}

void ThreadWorker::Jion( ThreadJob* job )
{
	m_job = job;
}

void ThreadWorker::Start()
{	
	if ( !m_busy )
	{
		pthread_mutex_lock( &m_t_mutex );  
		pthread_cond_wait( &m_t_cond, &m_t_mutex );  
		pthread_mutex_unlock( &m_t_mutex );
	}
	
	if ( m_job )
	{
		m_busy = true;
		m_job->Do();
	}
	
	m_busy = m_owner->Done( this );
}

void* PoolThreadFunc( void* param )
{
    ThreadWorker* worker = static_cast< ThreadWorker* >( param );
    if ( !worker )
        return NULL;

	while ( worker->Owner()->Running() )
	{
		worker->Start();
	}
}
