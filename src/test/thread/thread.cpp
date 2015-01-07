#include <pthread.h>
#include <iostream>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <unistd.h>


using namespace std;

bool flag = false;

pthread_attr_t tattr;

__thread int a = 3;

int b = 0;

void* ThreadFunc( void* param )
{
      pid_t pid = static_cast<pid_t>( ::syscall( SYS_gettid ) );
      cout << "pid:" << pid << ", a:" << a << endl;
      
      ::prctl(PR_SET_NAME, "ThreadFunc");
      
      sleep( 10 );
      
      b = 100;

      return (void*)&b;
}

int main( int argc, char* argv[] )
{
      a = 6;
      
      pthread_t tid;
      pthread_create( &tid, NULL, ThreadFunc, NULL );
      
      int* c = NULL;
      pthread_join( tid, (void**)&c );
      if (c)
          cout << "c:" << *c << endl;  
      
      return 0;
}