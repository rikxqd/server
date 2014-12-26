#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "net/warp_socket.h"


#define SERVER_PORT 3000

using namespace std;

pid_t Fork(void)
{
	pid_t	pid = fork();
	if ( -1 == pid )
		cout << "fork error" << endl;
	return pid;
}

void Close( int fd )
{
	if ( -1 == close( fd ) )
		cout << " close fd fail " << endl;
}

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
      
      pid_t childpid;      
      for ( ; ; )
      {
            struct sockaddr_in caddr = {0};
		socklen_t ca_len = sizeof(caddr);
		SOCKFD csock = Accept( ssock, (Address*)&caddr, &ca_len );

		if ( ( childpid = Fork() ) == 0) 
		{
			Close( ssock );
			// str_echo( csock );
			exit( 0 );
		}
		Close( csock );
	}
            
      exit( 0 );
}