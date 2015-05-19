#ifndef _THREAD_LOCK_H_
#define _THREAD_LOCK_H_

#include "public.h"


namespace Thread
{

class GuardLock
{
public:
	explicit GuardLock( ThreadMutex* mutex );
	~GuardLock();

private:
	ThreadMutex*	m_mutex;
};

int32 MutexInit( ThreadMutex* mutex, const ThreadMutexAttr* attr = NULL );

}// End of Thread

#endif//_THREAD_LOCK_H_
