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

}// End of Thread

#endif//_THREAD_LOCK_H_
