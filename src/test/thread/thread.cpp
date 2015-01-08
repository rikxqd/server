#include <pthread.h>
#include <iostream>
#include "thread/thread.h"


using namespace std;

class TestThread : public Thread
{
public:
      virtual void Run() 
      { 
            OnRun();
            cout << "running" << endl;
      }
};

void* ThreadFunc( void* param )
{
      Thread* thread = static_cast<Thread*>( param );
      if ( thread )
            thread->Run();

      return (void*)thread;
}

int main( int argc, char* argv[] )
{
      TestThread thread;
      
      pthread_t tid;
      pthread_create( &tid, NULL, ThreadFunc, &thread );
      
      Thread* c = NULL;
      pthread_join( tid, (void**)&c );
      
      return 0;
}