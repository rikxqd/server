#include "thread_api.h"

#include "global.h"


namespace Thread
{

namespace API
{
#ifdef WIN32
	//TODO
#elif UNIX
	int32 ThreadCreate( ThreadHandle* tidp, const ThreadAttr* attr, ThreadCallback func, void *arg )
	{
		int32 ret = pthread_create( tidp, attr, func, arg );
		if ( 0 != ret )
			 g_log.Fatal( "Thread create fatal" );

		return ret;
	}

	int32 ThreadJoin( ThreadHandle thread, void** retval )
	{
		return pthread_join( thread, retval );
	}

	int32 ThreadCondInit( ThreadCond* cond, const ThreadCondAttr* attr )
	{
		return pthread_cond_init( cond, attr );
	}

	void ThreadCondSignal( ThreadCond* cond )
	{
		pthread_cond_signal( cond );
	}

	void ThreadCondWait( ThreadCond* cond, ThreadMutex* mutex )
	{
		pthread_cond_wait( cond, mutex );
	}

	int32 MutexInit( ThreadMutex* mutex, const ThreadMutexAttr* attr )
	{
		return pthread_mutex_init( mutex, attr );
	}
#endif
}/* end of Thread::API */

}/* end of Thread */
