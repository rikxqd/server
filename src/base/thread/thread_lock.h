#ifndef _THREAD_LOCK_H_
#define _THREAD_LOCK_H_

#include <unistd.h>


class ThreadLock
{
public:
	ThreadLock( pthread_mutex_t& mutex )
		: m_mutex( mutex )
	{
		pthread_mutex_lock( &m_mutex );
	}
	~ThreadLock()
	{
		pthread_mutex_unlock( &m_mutex );
	}
private:
	pthread_mutex_t&	m_mutex;
};

#endif//_THREAD_LOCK_H_
