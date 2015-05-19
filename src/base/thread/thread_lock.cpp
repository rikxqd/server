#include "thread_lock.h"


namespace Thread
{

#ifdef WIN32
	//TODO
#elif UNIX
	GuardLock::GuardLock( ThreadMutex* mutex )
		: m_mutex( mutex )
	{
		pthread_mutex_lock( m_mutex );
	}

	GuardLock::~GuardLock()
	{
		pthread_mutex_unlock( m_mutex );
	}

	int32 MutexInit( ThreadMutex* mutex, const ThreadMutexAttr* attr )
	{
		return pthread_mutex_init( mutex, attr );
	}
#endif

}// End of Lock
