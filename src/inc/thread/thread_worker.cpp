#include "thread_worker.h"


void DefualtWorkerFunc( ThreadParam* param )
{
    cout << "this is the defualt worker func !" << endl;
}

ThreadWorker::ThreadWorker()
{
}

ThreadWorker::~ThreadWorker()
{
}

void ThreadWorker::Init( ThreadPool* pool )
{
    m_owner = pool;
    
    pthread_cond_init( &m_t_cond, NULL );
    pthread_mutex_init( &m_t_mutex, NULL );
    m_func = DefualtWorkerFunc;
    m_param = NULL;
}

bool ThreadWorker::Busy() const
{
    return m_busy;
}

pthread_t& ThreadWorker::Key()
{
    return m_t_tid;
}
pthread_cond_t& ThreadWorker::ThreadCond()
{
	return m_t_cond;
}
pthread_mutex_t& ThreadWorker::ThreadMutex()
{
	return m_t_mutex;
}

ThreadPool* ThreadWorker::Owner()
{
	return m_owner;
}

void ThreadWorker::Jion( WorkerFunc func, ThreadParam* param )
{
	m_func = func;
	m_param = param;
}

void ThreadWorker::Start()
{
	m_busy = true;
	WorkerFunc( m_param );
	m_busy = false;
}
