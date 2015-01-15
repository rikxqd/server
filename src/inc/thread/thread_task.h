#ifndef _THREAD_TASK_H_
#define _THREAD_TASK_H_


class TaskParam 
{
public:
    TaskParam();
    ~TaskParam();
    
	void* m_in_param; 
	void* m_out_param;
};

typedef void (*TaskHandle)( TaskParam* task );

class ThreadTask
{
    friend class ThreadWorker;
public:
    ThreadTask();
    ThreadTask( TaskHandle handle, TaskParam* param );
    ~ThreadTask();
    
    void Set( TaskHandle handle );
    void Set( TaskParam* param );

protected:
    void Do();

private:
    TaskHandle   m_handle;
    TaskParam*   m_param;
};

#endif//_THREAD_TASK_H_
