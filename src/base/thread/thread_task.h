#ifndef _THREAD_TASK_H_
#define _THREAD_TASK_H_

#include "public.h"
#include "utility/share_ptr.h"


class ThreadTask : public RefCounter
{
public:
    ThreadTask(){}
    ~ThreadTask(){}

	virtual void Process() = 0;
};

typedef SharePtr<ThreadTask> ThreadTaskPtr;

#endif//_THREAD_TASK_H_
