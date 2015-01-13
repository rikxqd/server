
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "public.h"
#include "thread/thread_pool.h"


void proc_fun( ThreadParam *job )
{
	int idx=*(int *)job->arg;  
	printf( "Begin: thread %d\n", idx );  
	sleep(3);  
	printf( "End:   thread %d\n", idx );  
} 

int main( int argc, char* argv[] )
{
	ThreadPool pool( 5, 10 );
	pool.Init();

	ThreadParam params[5];  
	int i, *idx;  

	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i;  
		params[i].arg = idx;  
		pool.Jion( proc_fun, params + i );  
		usleep( 400000 );  
	}

	printf( "All jobs done!\n" );  

	return 0;
}