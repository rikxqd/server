#include "thread_job.h"

#include "public.h"


void DefualtJobFunc( JobParam* param )
{
    cout << "this is the defualt job func !" << endl;
}

ThreadJob::ThreadJob()
    : m_param( NULL )
    , m_handle( DefualtJobFunc )
{
}

ThreadJob::~ThreadJob()
{
}

void ThreadJob::Set( JobHandle handle, JobParam* param )
{
    m_handle = handle;
    m_param = param;
}

void ThreadJob::Do()
{
    m_handle( m_param );
}
