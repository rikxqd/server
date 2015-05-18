#include "epoll.h"

#include <sys/epoll.h>

#include "global.h"


namespace Epoll
{

int32 EpollCreate( uint32 max )
{
	int32 fd = epoll_create( max );
	if ( -1 == fd )      
		FATAL( "epoll create fail ! errno:%d", errno );

	return fd;
}

}/* end of Epoll */