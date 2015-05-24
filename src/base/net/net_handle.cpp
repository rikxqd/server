#include "net_handle.h"


namespace Net
{

NetHandle::NetHandle( int32 domain, int32 type, int32 protocol )
{
	m_handle = Net::API::Socket( domain, type, protocol );
	if ( 0 > m_handle )
		m_handle = -1;
}

NetHandle::~NetHandle()
{
}

bool NetHandle::Init() const
{
	return (-1 != m_handle);
}

bool NetHandle::Bind( AddressPtr addr )
{
	if ( Init() )
		return false;

	int32 ret = Net::API::Bind( m_handle, &(addr->Get()), addr->Length() );
	return 0 > ret ? Close() : true;
}

bool NetHandle::Listen( int32 backlog )
{
	if ( Init() )
		return false;

	int32 ret = Net::API::Listen( m_handle, backlog );
	return 0 > ret ? Close() : true;
}

bool NetHandle::Close()
{
	if ( Init() )
		return false;

	Net::API::Close( m_handle );
	m_handle = -1;
	return false;
}

}
