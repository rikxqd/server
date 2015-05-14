#ifndef _THREAD_TASK_H_
#define _THREAD_TASK_H_


class ThreadTask
{
public:
    ThreadTask(){}
    ~ThreadTask(){}

	virtual void Do() = 0;
};

#endif//_THREAD_TASK_H_
