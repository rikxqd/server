#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "net/net_api.h"
#include "public.h"


#define	MAXLINE		4096	/* max text line length */

int main( int argc, char **argv )
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	
	if ( argc != 3 )
		LOG_DEBUG("usage: a.out <IPaddress>");

	LOG_DEBUG("argv[1]:%s\n", argv[1]);

	if ( ( sockfd = Net::API::Socket( AF_INET, SOCK_STREAM, 0 ) ) < 0)
		exit( -1 );

	bzero( &servaddr, sizeof servaddr );
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons( atoi( argv[2] ) );
	if ( inet_pton( AF_INET, argv[1], &servaddr.sin_addr ) <= 0)
		LOG_DEBUG("inet_pton error for %s\n", argv[1]);

	if ( Net::API::Connect( sockfd, (sockaddr*) &servaddr, sizeof servaddr ) < 0)
	{
		LOG_DEBUG("connect error\n");
		exit( -1 );
	}

	while ( ( n = read( sockfd, recvline, MAXLINE ) ) > 0) 
	{
		recvline[n] = 0;
		if ( fputs( recvline, stdout ) == EOF )
			LOG_DEBUG("fputs error\n");
	}
	if ( n < 0 )
		LOG_DEBUG("read error\n");

	exit( 0 );
}
