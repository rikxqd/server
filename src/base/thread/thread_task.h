#ifndef _THREAD_TASK_H_
#define _THREAD_TASK_H_

#include "public.h"


class ThreadTask
{
public:
    ThreadTask(){}
    ~ThreadTask(){}

	virtual void Process() = 0;
};

#endif//_THREAD_TASK_H_