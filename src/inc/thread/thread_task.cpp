#include "thread_task.h"

#include <unistd.h>

#include "process/process.h"
#include "global.h"


void DefualtTaskFunc( void* param )
{
    g_log.Info( "%d: this is the defualt task func !", ProcFunc::ProcId() );
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
