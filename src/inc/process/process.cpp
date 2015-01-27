#include "process.h"

#include <iostream>
#include <string.h>
#include <sys/syscall.h>

#include "global.h"


using namespace std;

#define BUF_SIZE 256

namespace ProcFunc
{

pid_t Fork(void)
{
	pid_t pid = fork();
	if ( -1 == pid )
		g_log.Fatal( "fork fatal" );

	return pid;
}

string ProcName()
{
	char file_name[BUF_SIZE] = {0};
	char path[BUF_SIZE] = {0};
	char* index = path;

	pid_t pid = getpid();

	snprintf( file_name, sizeof(file_name), "/proc/%d/exe", pid );
	int32 count = readlink( file_name, path, BUF_SIZE );
	if ( 0 > count  || BUF_SIZE <= count )
		return "";

	for( int32 i = count - 1 ; 0 <= i ; --i )
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
		return "";

	char name[BUF_SIZE] = {0};
	strncpy( name, index, sizeof(name) );
	return name;
}

pid_t ProcId()
{
	return static_cast< pid_t >( ::syscall( SYS_gettid ) );
}

}/* end of ProcFunc */
