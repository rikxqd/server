#ifndef _THREAD_H_
#define _THREAD_H_

#include "public.h"


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

#endif//_THREAD_H_
