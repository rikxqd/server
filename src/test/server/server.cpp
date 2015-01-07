#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "net/warp_socket.h"
#include "process/process.h"

#include "tinyxml.h"


#define SERVER_PORT 3000

int32 port = 0;
char ip[64] = "127.0.0.1";

using namespace std;

void Init()
{
	TiXmlDocument doc( "doc/config/test.xml" );
	if ( !doc.LoadFile() )
	{
		cout << "xml load fail " << endl;
		exit( -1 );
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* first = root->FirstChildElement("server");
	if ( first )
	{
		TiXmlElement* second = first->FirstChildElement("ip");
		if ( second )
			strcpy( ip, second->GetText() );

		second = first->FirstChildElement("port");
		if ( second )
			port = atoi( second->GetText() );
	}
}

int main( int argc, char* argv[] )
{
	Init();
      
	SOCKFD ssock = Socket( AF_INET, SOCK_STREAM, 0 );
	if ( 0 > ssock )
            exit( -1 );
            
	struct sockaddr_in saddr= {0};
	saddr.sin_family        = AF_INET;
	saddr.sin_port          = htons( port );
	//saddr.sin_addr.s_addr	= inet_addr( ip );
	saddr.sin_addr.s_addr   = htonl( INADDR_ANY );

	int32 res = Bind( ssock, (sockaddr*)&saddr, sizeof saddr );
	if ( 0 > res )
		exit( -1 );
            
	res = Listen( ssock, 1024 );
	if ( 0 > res )
		exit( -1 );
            
	for ( ; ; )
	{
		struct sockaddr_in caddr = {0};
		socklen_t ca_len = sizeof(caddr);
		SOCKFD csock = Accept( ssock, (sockaddr*)&caddr, &ca_len );

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
