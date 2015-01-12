#include "process.h"

#include <iostream>
#include <string.h>

using namespace std;

#define BUF_SIZE 256

pid_t Fork(void)
{
	pid_t	pid = fork();
	if ( -1 == pid )
		cout << "fork error" << endl;
	return pid;
}

int32 ProcName( char* name, uint32 size )
{
	char file_name[BUF_SIZE] = {0};
	char path[BUF_SIZE] = {0};
	char* index = path;

	pid_t pid = getpid();

	snprintf( file_name, sizeof(file_name), "/proc/%d/exe", pid );
	int32 count = readlink( file_name, path, BUF_SIZE );
	if ( 0 > count  || BUF_SIZE <= count )
		return -1;

	int32 i = count - 1;
	for( ; 0 <= i ; i-- )
	{
		if( '/' == path[i] )//筛选出进程名
		{
			++i;
			index += i;
			break; 
		}
	}

	int32 len = strlen( index );
	if ( 0 == len )
		return -1;

	strncpy( name, index, size );
	return 0;
}
