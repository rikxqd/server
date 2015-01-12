#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include "log/log.h"

using namespace std;

#define CFGMNG_TASK_NAME_LEN 256

int cfgmng_get_taskname(char *ac, int len)
{
    int count = 0;
    int nIndex = 0;
    char chPath[CFGMNG_TASK_NAME_LEN] = {0};
    char cParam[100] = {0};
    char *cTem = chPath;
    int tmp_len;

    pid_t pId = getpid();
    sprintf(cParam,"/proc/%d/exe",pId);
/*    printf("cParam = %s.\n", cParam);*/
    count = readlink(cParam, chPath, CFGMNG_TASK_NAME_LEN);
/*    printf("count = %d.\n", count);*/
    if (count < 0 || count >= CFGMNG_TASK_NAME_LEN)
    {
        printf("Current System Not Surport Proc.\n");
        return -1;
    }
    // else
    // {
    //     nIndex = count - 1;

    //     for( ; nIndex >= 0; nIndex--)
    //     {
    //         if( chPath[nIndex] == '/' )//筛选出进程名
    //         {
    //             nIndex++;
    //             cTem += nIndex;
    //             break; 
    //         }
    //     }
    // }
    tmp_len = strlen(cTem);
    if (0 == tmp_len) {
        printf("Get task fail.\n");
        return -1;
    }
    
    if (len <= tmp_len +1) {
        printf("len(%d) is less than taskname(%s)'s len.\n", len, cTem);
        return -1;
    }
    
    strcpy(ac, cTem);
    
    return 0;
}

int main()
{
    Log log( "test" );
    
    log.Debug( "Debug" );
    log.Info( "Info" );
    log.Warning( "Warning" );
    log.Error( "Error" );
    log.Fatal( "Fatal" );
    
    int ret;
    char ac_tmp[CFGMNG_TASK_NAME_LEN];
    ret = cfgmng_get_taskname(ac_tmp, CFGMNG_TASK_NAME_LEN);
    if (0 != ret) 
    {
        printf("Call cfgmng_get_taskname fail.\n");
        return -1;
    }
    printf("The running task name is %s .\n", ac_tmp);
    
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