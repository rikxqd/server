#include <iostream>
#include <memory>

#include "function/function.h"


using namespace std;

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
      Function< void ( void* ) > f;
      
      print( 123, 3.14, "tair" );
      
      return 0;
}
