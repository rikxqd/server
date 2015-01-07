#ifndef _WARP_SOCKET_H_
#define _WARP_SOCKET_H_

#include <netinet/in.h>
#include "public.h"

#ifdef WIN32

#elif UNIX
      typedef int32 SOCKFD;
#endif

SOCKFD Socket( int32 domain, int32 type, int32 protocol );

int32 Connect( int32 sockfd, const sockaddr* addr, socklen_t addrlen );

int32 Bind( int32 sockfd, const sockaddr* sa, socklen_t salen );

int32 Listen( int32 sockfd, int32 backlog );

SOCKFD Accept( int32 sockfd, sockaddr* sa, socklen_t* len );

#endif//_WARP_SOCKET_H_
