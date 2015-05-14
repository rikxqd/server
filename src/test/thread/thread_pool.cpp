#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <stdlib.h>

#include "global.h"
#include "public.h"
#include "thread/thread_pool.h"
#include "thread/thread_task.h"
#include "process/process.h"


class TestThread : public ThreadTask
{
public:
	TestThread( int32 param )
		: m_param( param )
	{
	}
	~TestThread(){}

	virtual void Do()
	{
		g_log.Debug( "%d: Begin: \t thread --- %d\n", ProcFunc::ProcId(), m_param );
		g_log.Debug( "%d: End: \t thread --- %d\n", ProcFunc::ProcId(), m_param );
	}

private:
	int32 m_param;
};

int main( int argc, char* argv[] )
{
	ThreadPool::Instance().Start();

	int32 i;  
	for( i = 0 ; i < 10 ; ++i )
	{
		TestThread* thread = new TestThread( i ); 
		ThreadPool::Instance().Join( thread );  
	}

	sleep( 20 );

	for( i = 0 ; i < 600 ; ++i )
	{
		TestThread* thread = new TestThread( i + 600 );
		ThreadPool::Instance().Join( thread );  
	}

	ThreadPool::Instance().Stop();

	g_log.Debug( "All tasks done!\n" );

	return 0;
}