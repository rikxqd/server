
#include <iostream>
#include <memory>
#include "thread/thread.h"
#include "function/function.h"


using namespace std;

class TestThread : public IThread::Thread
{
public:
      TestThread(){}
      ~TestThread(){}
      
      virtual void Run() 
      { 
            OnRun();
            cout << "running" << endl;
      }
};

void print()
{
      cout << endl;
}
 
template < typename T, typename... Args >
void print( const T &t, const Args&... args )
{
      cout << t << " ";
      print( args... );
}

int main( int argc, char* argv[] )
{
      TestThread thread;
      
      pthread_t tid = IThread::Run( &thread );
      
      IThread::Thread* c = NULL;
      pthread_join( tid, (void**)&c );
      
      
      Function< void ( void* ) > f;
      
      print(123, 3.14, "tair");
      
      return 0;
}