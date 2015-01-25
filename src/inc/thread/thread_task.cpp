#include "thread_task.h"

#include "public.h"


void DefualtTaskFunc( void* param )
{
    cout << "this is the defualt task func !" << pthread_self() << endl;
}

ThreadTask::ThreadTask()
    : m_handle( DefualtTaskFunc )
    , m_param( NULL )
{
}

ThreadTask::ThreadTask( TaskHandle handle, void* param )
    : m_handle( handle )
    , m_param( param )
{
}

ThreadTask::~ThreadTask()
{
}

void ThreadTask::Set( TaskHandle handle )
{
    m_handle = handle;
}

void ThreadTask::Set( void* param )
{
    m_param = param;
}

void ThreadTask::Do()
{
    m_handle( m_param );
}
