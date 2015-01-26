#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>

#include "global.h"
#include "thread/thread_pool.h"
#include "thread/thread_task.h"


void Func( void *param )
{
	int idx = *(int *)param;  
	printf( "Begin[%d]: thread %d\n", idx, static_cast<pid_t>(::syscall(SYS_gettid)) );  
	sleep( 10 );  
	printf( "End[%d]:   thread %d\n", idx, static_cast<pid_t>(::syscall(SYS_gettid)) );
} 

int main( int argc, char* argv[] )
{
	g_thread_pool.Start();

	int i, *idx;  
	for( i = 0 ; i < 10 ; ++i )
	{
		idx = (int*)malloc( sizeof(int) );  
		*idx = i;  
		g_thread_pool.Join( Func, idx );  
	}

	g_thread_pool.Stop();

	printf( "All tasks done!\n" );  

	return 0;
}