#include "thread_task.h"

#include "public.h"


void DefualtTaskFunc( TaskParam* param )
{
    cout << "this is the defualt task func !" << endl;
}

TaskParam::TaskParam()
    : m_in_param( NULL )
	, m_out_param( NULL )
{
}

TaskParam::~TaskParam()
{
}

ThreadTask::ThreadTask()
    : m_handle( DefualtTaskFunc )
    , m_param( NULL )
{
}

ThreadTask::ThreadTask( TaskHandle handle, TaskParam* param )
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

void ThreadTask::Set( TaskParam* param )
{
    m_param = param;
}

void ThreadTask::Do()
{
    m_handle( m_param );
}
