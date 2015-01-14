
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "public.h"
#include "thread/thread_pool.h"
#include "thread/thread_job.h"


void Func( JobParam *job )
{
	int idx = *(int *)job->m_in_param;  
	printf( "Begin: thread %d\n", idx );  
	sleep( 3 );  
	printf( "End:   thread %d\n", idx );  
} 

int main( int argc, char* argv[] )
{
	ThreadPool pool( 5, 10 );
	pool.Init();
	sleep( 1 );

	JobParam params[5];  
	int i, *idx;  

	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i;  
		params[i].m_in_param = idx;
		ThreadJob job;
		job.Set( Func, params + i );
		pool.Jion( &job );  
		usleep( 400000 );  
	}
	
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 5;  
		params[i].m_in_param = idx;
		ThreadJob job;
		job.Set( Func, params + i );
		pool.Jion( &job );  
		usleep( 400000 );  
	}
	
	sleep( 6 );
	
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 10;  
		params[i].m_in_param = idx;
		ThreadJob job;
		job.Set( Func, params + i );
		pool.Jion( &job );  
		usleep( 400000 );  
	}
	
	sleep( 6 );

	printf( "All jobs done!\n" );  

	return 0;
}