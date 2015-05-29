#include "net_handle.h"


namespace Net
{

NetHandle::NetHandle( SockFd sock )
	: m_handle( sock )
{
}

NetHandle::NetHandle( int32 domain, int32 type, int32 protocol )
{
	m_handle = Net::API::Socket( domain, type, protocol );
	if ( 0 > m_handle )
		m_handle = -1;
}

NetHandle::~NetHandle()
{
	DEBUG( "NetHandle::~NetHandle" );
	Close();
}

SockFd NetHandle::Get() const
{
	return m_handle;
}

bool NetHandle::Valid() const
{
	return (-1 != m_handle);
}

bool NetHandle::Bind( AddressPtr addr )
{
	if ( !Valid() )
		return false;

	int32 ret = Net::API::Bind( m_handle, &(addr->Get()), addr->Length() );
	return 0 > ret ? Close() : true;
}

bool NetHandle::Listen( int32 backlog )
{
	if ( !Valid() )
		return false;

	int32 ret = Net::API::Listen( m_handle, backlog );
	return 0 > ret ? Close() : true;
}

NetHandlePtr NetHandle::Accept( AddressPtr addr )
{
	if ( !Valid() )
		return NULL;

	uint32 len = addr->Length();
	int32 ret = Net::API::Accept( m_handle, &(addr->m_addr), &len );

#ifdef WIN32
	return INVALID_SOCKET == ret ? NULL : new NetHandle( ret );
#elif UNIX
	return 0 > ret ? NULL : new NetHandle( ret );
#endif
}

int32 NetHandle::SetNonBlocking( bool non_blocking )
{
	return Net::API::Fcntl( m_handle, non_blocking );
}

int32 NetHandle::SetNoDelay( bool no_delay )
{
	return Net::API::SetSockOpt( m_handle, no_delay );
}

bool NetHandle::Close()
{
	if ( !Valid() )
		return false;

	Net::API::Close( m_handle );
	m_handle = -1;
	return false;
}

}
