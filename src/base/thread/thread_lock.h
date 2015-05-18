#ifndef _THREAD_LOCK_H_
#define _THREAD_LOCK_H_

#include "public.h"


class GuardLock
{
public:
	GuardLock( pthread_mutex_t& mutex )
		: m_mutex( mutex )
	{
		pthread_mutex_lock( &m_mutex );
	}
	~GuardLock()
	{
		pthread_mutex_unlock( &m_mutex );
	}
private:
	ThreadMutex&	m_mutex;
};

#endif//_THREAD_LOCK_H_
