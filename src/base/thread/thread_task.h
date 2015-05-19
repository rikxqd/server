#ifndef _THREAD_TASK_H_
#define _THREAD_TASK_H_

#include "utility/share_ptr.h"


namespace Thread
{

class ThreadTask : public RefCounter
{
public:
    ThreadTask(){}
    virtual ~ThreadTask(){}

	virtual void Process() = 0;
};

typedef SharePtr<ThreadTask> ThreadTaskPtr;

}// End of Thread

#endif//_THREAD_TASK_H_
