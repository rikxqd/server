#ifndef _THREAD_FUNC_H_
#define _THREAD_FUNC_H_

#include "public.h"


namespace Thread
{

namespace API
{
	typedef void* (*ThreadCallback)(void*);
	int32 ThreadCreate( ThreadHandle* tidp, const ThreadAttr *attr, ThreadCallback func, void *arg );
	int32 ThreadJoin( ThreadHandle thread, void** retval = NULL );
	int32 ThreadCondInit( ThreadCond* cond, const ThreadCondAttr* attr );
	void ThreadCondSignal( ThreadCond* cond );
	void ThreadCondWait( ThreadCond* cond, ThreadMutex* mutex );
	int32 MutexInit( ThreadMutex* mutex, const ThreadMutexAttr* attr = NULL );
}

}// End of Thread

#endif//_THREAD_FUNC_H_
