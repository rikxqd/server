#ifndef _SOCK_FUNC_H_
#define _SOCK_FUNC_H_

#include <netinet/in.h>
#include "public.h"


#ifdef WIN32

#elif UNIX
      typedef int32 SOCKFD;
#endif

namespace SockFunc
{

SOCKFD Socket( int32 domain, int32 type, int32 protocol );

int32 Connect( int32 sockfd, const sockaddr* addr, socklen_t addrlen );

int32 Bind( int32 sockfd, const sockaddr* sa, socklen_t salen );

int32 Listen( int32 sockfd, int32 backlog );

SOCKFD Accept( int32 sockfd, sockaddr* sa, socklen_t* len );

}/* end of SockFunc */

#endif//_SOCK_FUNC_H_
