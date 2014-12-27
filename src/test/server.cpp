#include <iostream>
#include <stdlib.h>

#include "net/warp_socket.h"
#include "process/process.h"


#define SERVER_PORT 3000

using namespace std;

int main( int argc, char* argv[] )
{
      SOCKFD ssock = Socket( AF_INET, SOCK_STREAM, 0 );
      if ( 0 > ssock )
            exit( -1 );
            
      struct sockaddr_in saddr= {0};
      saddr.sin_family        = AF_INET;
      saddr.sin_port          = htons( SERVER_PORT );
      saddr.sin_addr.s_addr   = htonl( INADDR_ANY );
      
      int32 res = Bind( ssock, (Address*)&saddr, sizeof saddr );
      if ( 0 > res )
            exit( -1 );
            
      res = Listen( ssock, 1024 );
      if ( 0 > res )
            exit( -1 );
            
      for ( ; ; )
      {
            struct sockaddr_in caddr = {0};
		socklen_t ca_len = sizeof(caddr);
		SOCKFD csock = Accept( ssock, (Address*)&caddr, &ca_len );

            pid_t childpid = Fork();
		if ( 0 == childpid ) 
		{
			close( ssock );
			// str_echo( csock );
			exit( 0 );
		}
		close( csock );
	}
            
      exit( 0 );
}