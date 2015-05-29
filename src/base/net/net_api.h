#ifndef _NET_API_H_
#define _NET_API_H_

#include <netinet/in.h>
#include "public.h"


namespace Net
{

namespace API
{

SockFd Socket( int32 domain, int32 type, int32 protocol );

int32 Connect( SockFd sock, const sockaddr* addr, socklen_t len );

int32 Bind( SockFd sock, const sockaddr* sa, socklen_t len );

int32 Bind( SockFd sock, const sockaddr_in* sa, socklen_t len );

int32 Listen( SockFd sock, int32 backlog );

SockFd Accept( SockFd sock, sockaddr* sa, socklen_t* len );

SockFd Accept( SockFd sock, sockaddr_in* sa, socklen_t* len );

int32 Fcntl( SockFd sock, bool non_blocking );

int32 SetSockOpt( SockFd sock, bool no_delay );

void Close( int32 fd );

}/* end of Net::API */

}/* end of Net */

#endif//_NET_API_H_
