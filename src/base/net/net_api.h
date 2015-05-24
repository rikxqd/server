#ifndef _NET_API_H_
#define _NET_API_H_

#include <netinet/in.h>
#include "public.h"


namespace Net
{

namespace API
{

SockFd Socket( int32 domain, int32 type, int32 protocol );

int32 Connect( int32 sock, const sockaddr* addr, socklen_t addrlen );

int32 Bind( int32 sock, const sockaddr* sa, socklen_t salen );

int32 Bind( int32 sock, const sockaddr_in* sa, socklen_t salen );

int32 Listen( int32 sock, int32 backlog );

SockFd Accept( int32 sock, sockaddr* sa, socklen_t* len );

void Close( int32 sock );

}/* end of Net::API */

}/* end of Net */

#endif//_NET_API_H_
