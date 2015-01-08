#ifndef _THREAD_H_
#define _THREAD_H_

#include "public.h"

#include <pthread.h>


namespace IThread
{

class Thread
{
public:
      Thread(){}
      virtual ~Thread(){}
      
      virtual void Run() = 0;
      
      virtual void OnRun();
      
      void Name( const char* name );
      const char* Name() const;
      
      static int32 Key();
};

pthread_t Run( Thread* thread );

}

#endif//_THREAD_H_
