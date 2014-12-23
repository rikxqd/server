#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define	MAXLINE		4096	/* max text line length */

int Socket( int domain, int type, int protocol )
{
	return socket( domain, type, protocol );
}

int Connect( int sockfd, const struct sockaddr *addr, socklen_t addrlen )
{
	return connect( sockfd, addr, addrlen );
}

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	
	if (argc != 2)
		printf("usage: a.out <IPaddress>");

	if ( (sockfd = Socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s", argv[1]);

	if (Connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		printf("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			printf("fputs error");
	}
	if (n < 0)
		printf("read error");

	exit(0);
}
