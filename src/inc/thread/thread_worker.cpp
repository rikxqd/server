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