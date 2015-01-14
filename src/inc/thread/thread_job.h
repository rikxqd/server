#ifndef _THREAD_JOB_H_
#define _THREAD_JOB_H_


class JobParam 
{
public:
	void* m_in_param; 
	void* m_out_param;
};

typedef void (*JobHandle)( JobParam* job );

class ThreadJob
{
    friend class ThreadWorker;
public:
    ThreadJob();
    ~ThreadJob();
    
    void Set( JobHandle handle, JobParam* param );

protected:
    void Do();

private:
    JobHandle   m_handle;
    JobParam*   m_param;
};

#endif//_THREAD_JOB_H_
