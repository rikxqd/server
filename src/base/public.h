#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <iostream>
#include <string>
#include <tr1/memory>

#include "define/integer.h"


using namespace std;

// 最大值，最小值
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// 禁止拷贝
class NonCopyable  
{  
protected:  
      NonCopyable() {}
      ~NonCopyable() {}  
private:
      NonCopyable( const NonCopyable& );  
      const NonCopyable& operator=( const NonCopyable& );  
};

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
	typedef sockaddr_in				SockAddress;
#endif

#endif//_PUBLIC_H_
