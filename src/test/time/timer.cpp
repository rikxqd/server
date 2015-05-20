#include <stdio.h>

#include "global.h"
#include "time/timer.h"
#include "time/timer_manager.h"
#include "thread/thread_pool.h"
#include "time/time.h"


void func( Timer* timer, void* param )  
{  
	printf( "hi,%d\n", *((int*)param) );  
} 

int main( int argc, char* argv[] )
{
	Thread::ThreadPoolPtr pool = new Thread::ThreadPool( 5 );
	pool->Start();
	TimerManager::Instance().Start( pool );
	g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

	int param[4] = {1,2,3,4};

	Timer* a = new Timer( 1000, func, param, Timer::TIMER_TYPE_CIRCLE );  
	Timer* a1 = new Timer( 2000, func, param+1, Timer::TIMER_TYPE_ONCE );  
	Timer* a2 = new Timer( 3000, func, param+2, Timer::TIMER_TYPE_CIRCLE );  
	Timer* a3 = new Timer( 1000, func, param+3, Timer::TIMER_TYPE_ONCE );  

	a->Start();
	a1->Start();
	a2->Start();
	a3->Start();

	g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );

	Time::SleepMsec( 12 * 1000 );

	return 0;
}