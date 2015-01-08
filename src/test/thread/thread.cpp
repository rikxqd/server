
#include <iostream>
#include "thread/thread.h"


using namespace std;

class TestThread : public IThread::Thread
{
public:
      virtual void Run() 
      { 
            OnRun();
            cout << "running" << endl;
      }
};

int main( int argc, char* argv[] )
{
      TestThread thread;
      
      pthread_t tid = IThread::Run( &thread );
      
      IThread::Thread* c = NULL;
      pthread_join( tid, (void**)&c );
      
      return 0;
}