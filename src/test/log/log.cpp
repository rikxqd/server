#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include "process/process.h"
#include "global.h"

using namespace std;

int main()
{
    DEBUG( "Debug %s", "Debug" );
    g_log.Info( "Info" );
    g_log.Warning( "Warning" );
    g_log.Error( "Error" );
    g_log.Fatal( "Fatal" );
    
    int ret;
	char proc_name[256] = {0};
    ret = ProcName( proc_name, sizeof(proc_name) );
    if ( 0 > ret ) 
        return -1;

    printf( "The running task name is %s \n", proc_name );
    
    // int i, j;
    // for(i=40; i<48; i++)
    // {
    //     for(j=30; j<38; j++)
    //     {
    //         //printf("\x1b[%d;%dm%s\n\x1b[0m",i, j, "你好~");
    //         cout << "\x1b[" << i << ";" << j <<"m" << "你好~" << "\033[0m" << endl;
    //     }
    // }

    return 0;
}