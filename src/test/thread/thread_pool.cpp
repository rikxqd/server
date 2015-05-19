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
#include "time/time.h"


using namespace Thread;

class TestThread : public ThreadTask
{
public:
	TestThread( int32 param, int32 rand_num = 0 )
		: m_param( param )
		, m_rand_num( rand_num )
	{
	}
	~TestThread(){}

	virtual void Process()
	{
		int32 r = rand() % 2000;
		g_log.Debug( "%d: Begin: \t thread --- %d_%d, wait %d ms\n", ProcFunc::ProcId(), m_param, m_rand_num, r );
		Time::SleepMsec( r );
		g_log.Debug( "%d: End: \t thread --- %d\n", ProcFunc::ProcId(), m_param );
	}

private:
	int32 m_param;
	int32 m_rand_num;
};

int main( int argc, char* argv[] )
{
	ThreadPool::Instance().Start();

	int32 i;  
	for( i = 0 ; i < 10 ; ++i )
		ThreadPool::Instance().Join( new TestThread( i ) );

	sleep( 20 );

	for( i = 0 ; i < 20 ; ++i )
	{
		int32 r = rand() % 2000;
		Time::SleepMsec( r );
		ThreadPool::Instance().Join( new TestThread( i + 20, r ) );
	}

	ThreadPool::Instance().Stop();

	g_log.Debug( "All tasks done!\n" );

	return 0;
}
