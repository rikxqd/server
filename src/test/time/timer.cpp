#include <stdio.h>

#include "global.h"
#include "time/timer.h"
#include "time/timer_manager.h"
#include "thread/thread_pool.h"
#include "time/time.h"


class TestTimer : public Timer
{
public:
	TestTimer( uint32 interval, int32 param, ETimerType type = TIMER_TYPE_ONCE )
		: Timer( interval, type )
		, m_count( 0 )
		, m_param( param )
	{
	}
	virtual ~TestTimer()
	{
	}

	virtual void TimeOut()
	{
		g_log.Debug( "TestTimer%d: %d", m_param, m_count++ );
	}

private:
	int32 m_count;
	int32 m_param;
};

typedef SharePtr<TestTimer> TestTimerPtr;

int main( int argc, char* argv[] )
{
	{
		Thread::ThreadPoolPtr pool = new Thread::ThreadPool( 5 );
		pool->Start();
		TimerManager::Instance().Start( pool );
		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

		int param[4] = {1,2,3,4};

		TestTimerPtr a( new TestTimer( 1000, param[0], Timer::TIMER_TYPE_CIRCLE ) );  
		TestTimerPtr a1( new TestTimer( 2000, param[1], Timer::TIMER_TYPE_ONCE ) );  
		TestTimerPtr a2( new TestTimer( 3000, param[2], Timer::TIMER_TYPE_CIRCLE ) );  
		TestTimerPtr a3( new TestTimer( 1000, param[3], Timer::TIMER_TYPE_ONCE ) );  

		a->Start();
		a1->Start();
		a2->Start();
		a3->Start();

		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

		Time::SleepMsec( 12 * 1000 );
		TimerManager::Instance().Stop();
		Time::SleepMsec( 5 * 1000 );
		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );
	}

	g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

	return 0;
}