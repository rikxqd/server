#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <stdlib.h>

#include "global.h"
#include "thread/thread_pool.h"
#include "thread/thread_task.h"
#include "process/process.h"


void Func( void *param )
{
	int idx = *(int *)param;  
	g_log.Debug( "%d: Begin: \t thread --- %d\n",  ProcFunc::ProcId(), idx );  
	sleep( rand() % 10 + 1 );  
	g_log.Debug( "%d: End: \t thread --- %d\n", ProcFunc::ProcId(), idx );
} 

int main( int argc, char* argv[] )
{
	ThreadPool::Instance().Start();

	int i, *idx;  
	for( i = 0 ; i < 10 ; ++i )
	{
		idx = (int*)malloc( sizeof(int) );  
		*idx = i;  
		ThreadPool::Instance().Join( Func, idx );  
	}

	sleep( 20 );

	for( i = 0 ; i < 600 ; ++i )
	{
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 600;  
		ThreadPool::Instance().Join( Func, idx );  
	}

	ThreadPool::Instance().Stop();

	g_log.Debug( "All tasks done!\n" );

	return 0;
}