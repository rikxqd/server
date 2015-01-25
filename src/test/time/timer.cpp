#include <stdio.h>

#include "time/timer.h"
#include "time/timer_manager.h"
#include "time/time.h"
#include "global.h"

void func( Timer* timer, void* param )  
{  
	printf( "hi,%d\n", *((int*)param) );  
} 

int main( int argc, char* argv[] )
{
	g_thread_pool.Init();
	TimerManager::Instance().Start();

	int param[4] = {1,2,3,4};

	Timer* a = new Timer( 1000, func, param, Timer::TIMER_CIRCLE );  
	Timer* a1 = new Timer( 2000, func, param+1, Timer::TIMER_ONCE );  
	Timer* a2 = new Timer( 3000, func, param+2, Timer::TIMER_ONCE );  
	Timer* a3 = new Timer( 1000, func, param+3, Timer::TIMER_ONCE );  

	a->Start();
	a1->Start();
	a2->Start();
	a3->Start();

	Time::SleepMsec( 12 * 1000 );

	return 0;
}