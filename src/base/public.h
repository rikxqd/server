#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <iostream>
#include <string>

#include "define/integer.h"
#include "utility/non_copyable.h"
#include "log/log.h"


// 最大值，最小值
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// 删除指针
#define DELETE_VALUE(_ptr)	\
	if((_ptr)) { delete (_ptr); (_ptr) = NULL; };
#define DELETE_ARRAY(_ptr)	\
	if((_ptr)) { delete[] (_ptr); (_ptr) = NULL; };

// 字符串格式化
#ifdef WIN32
#define snprintf sprintf_s
#endif

// BUFFER大小
#define BUF_MIN	(1 << 5)
#define BUF_MED	(1 << 10)
#define BUF_MAX	(1 << 20)

// 线程
#ifdef WIN32

#elif UNIX
	#include <unistd.h>
	typedef pthread_mutex_t			ThreadMutex;
	typedef pthread_mutexattr_t		ThreadMutexAttr;
	typedef pthread_cond_t			ThreadCond;
	typedef pthread_condattr_t		ThreadCondAttr;
	typedef pthread_t				ThreadHandle;
	typedef pthread_attr_t			ThreadAttr;
#endif

// 网络
#ifdef WIN32

#elif UNIX
	#include <netinet/in.h>
	typedef int32					SockFd;
	typedef sockaddr_in				SockAddr;
#endif

// 日志
#define DEBUG( buffer, ... )	\
	Log::Instance().Pattern( {__FILE__, __LINE__}, Log::LOG_DEBUG, buffer, ##__VA_ARGS__ )
#define INFO( buffer, ... )	\
	Log::Instance().Pattern( {__FILE__, __LINE__}, Log::LOG_INFO, buffer, ##__VA_ARGS__ )
#define WARN( buffer, ... )	\
	Log::Instance().Pattern( {__FILE__, __LINE__}, Log::LOG_WARNING, buffer, ##__VA_ARGS__ )
#define ERROR( buffer, ... )	\
	Log::Instance().Pattern( {__FILE__, __LINE__}, Log::LOG_ERROR, buffer, ##__VA_ARGS__ )
#define FATAL( buffer, ... )	\
	Log::Instance().Pattern( {__FILE__, __LINE__}, Log::LOG_FATAL, buffer, ##__VA_ARGS__ )

#endif//_PUBLIC_H_
