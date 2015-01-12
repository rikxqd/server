#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <unistd.h>

#include "public.h"


pid_t Fork(void);

int32 ProcName( char* name, uint32 size );

#endif//_PROCESS_H_
