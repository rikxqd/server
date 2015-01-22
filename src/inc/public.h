#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <iostream>
#include <string>

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

#ifdef WIN32
#define snprintf sprintf_s
#endif

#define BUF_MIN	(1 << 5)
#define BUF_MED	(1 << 10)
#define BUF_MAX	(1 << 20)

#endif//_PUBLIC_H_
