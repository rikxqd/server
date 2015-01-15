
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "public.h"
#include "thread/thread_pool.h"
#include "thread/thread_task.h"


void Func( TaskParam *task )
{
	int idx = *(int *)task->m_in_param;  
	printf( "Begin: thread %d\n", idx );  
	sleep( 3 );  
	printf( "End:   thread %d\n", idx );
	int* ret = (int*)malloc( sizeof(int) );
	*ret = idx;
	task->m_out_param = ret;
} 

int main( int argc, char* argv[] )
{
	ThreadPool pool( 5, 10 );
	pool.Init();
	sleep( 1 );

	TaskParam params[15];  
	int i, *idx;  

	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i;  
		params[i].m_in_param = idx;
		pool.Jion( Func, params + i );  
	}
	
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 20;  
		params[i + 5].m_in_param = idx;
		pool.Jion( Func, params + i + 5 );  
	}
	
	sleep( 6 );
	
	for( i = 0 ; i < 5 ; ++i )
	{  
		idx = (int*)malloc( sizeof(int) );  
		*idx = i + 50;  
		params[i + 10].m_in_param = idx;
		pool.Jion( Func, params + i + 10 );  
	}
	
	sleep( 6 );
	
	for ( i = 0 ; i < 15 ; ++i )
	{
		int idx = *(int *)params[i].m_out_param;
		printf( "out param : %d, %d\n", i, idx );
	}

	printf( "All tasks done!\n" );  

	return 0;
}