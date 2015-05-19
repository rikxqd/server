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
#endif

}// End of Lock
