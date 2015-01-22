
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "public.h"
#include "thread/thread_pool.h"
#include "thread/thread_task.h"


void Func( void *param )
{
	int idx = *(int *)param;  
	printf( "Begin: thread %d\n", idx );  
	sleep( 3 );  
	printf( "End:   thread %d\n", idx );
} 

int main( int argc, char* argv[] )
{
	ThreadPool pool( 5, 10 );
	pool.Init();

	int i, *idx;  
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i;  
		pool.Join( Func, idx );  
	}
	
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 20;  
		pool.Join( Func, idx );  
	}
	
	sleep( 6 );
	
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 50;  
		pool.Join( Func, idx );  
	}
	pool.Stop();

	printf( "All tasks done!\n" );  

	return 0;
}