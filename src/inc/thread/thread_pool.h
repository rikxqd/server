#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "singleton/singleton.h"


class ThreadPool : public Singleton< ThreadPool >
{
	friend class Singleton< ThreadPool >;
public:
	ThreadPool();
	~ThreadPool();

	void Jion();

private:

};

#endif//_THREAD_POOL_H_
