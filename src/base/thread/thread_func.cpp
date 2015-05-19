#include "thread_func.h"


namespace Thread
{

namespace API
{
	int32 ThreadCreate( ThreadHandle* tidp, const ThreadAttr* attr, ThreadCallback func, void *arg )
	{
		return pthread_create( tidp, attr, func, arg );
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
}

}// End of Thread
