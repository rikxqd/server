#ifndef _THREAD_TASK_H_
#define _THREAD_TASK_H_


typedef void (*TaskHandle)( void* task );

class ThreadTask
{
    friend class ThreadWorker;
public:
    ThreadTask();
    ThreadTask( TaskHandle handle, void* param );
    ~ThreadTask();
    
    void Set( TaskHandle handle );
    void Set( void* param );

protected:
    void Do();

private:
    TaskHandle   m_handle;
    void*			m_param;
};

#endif//_THREAD_TASK_H_
