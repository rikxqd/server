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
		g_log.Debug( "%d: Begin: \t thread --- %d_%d, wait %d ms", ProcFunc::ProcId(), m_param, m_rand_num, r );
		Time::SleepMsec( r );
		g_log.Debug( "%d: End: \t thread --- %d", ProcFunc::ProcId(), m_param );
	}

private:
	int32 m_param;
	int32 m_rand_num;
};

int main( int argc, char* argv[] )
{
	{
		ThreadPoolPtr pool = new ThreadPool( 4 );
		pool->Start();
		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

		int32 i;  
		for( i = 0 ; i < 10 ; ++i )
			pool->Join( new TestThread( i ) );

		Time::SleepMsec( 20 * 1000 );
		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

		for( i = 0 ; i < 20 ; ++i )
		{
			int32 r = rand() % 2000;
			Time::SleepMsec( r );
			pool->Join( new TestThread( i + 20, r ) );
		}

		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );
		pool->Stop();
		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );
	}

	g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

	return 0;
}
