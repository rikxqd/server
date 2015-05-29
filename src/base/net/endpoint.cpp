#include "endpoint.h"
#include "global.h"


namespace Net
{

Endpoint::Endpoint()
{
}

Endpoint::Endpoint( AddressPtr addr, NetHandlePtr net_handle )
	: m_addr( addr )
	, m_net_handle( net_handle )
{
}

Endpoint::~Endpoint()
{
}

bool Endpoint::Valid() const
{
	return m_net_handle->Valid();
}

bool Endpoint::Init( std::string ip, uint16 port )
{
	m_addr = new Address( ip.c_str(), port );
	m_net_handle = new NetHandle( AF_INET, SOCK_STREAM, 0 );
	m_net_handle->SetNonBlocking( true );
	m_net_handle->SetNoDelay( true );
	return m_net_handle->Valid();
}

bool Endpoint::Bind()
{
	return m_net_handle->Bind( m_addr );
}

bool Endpoint::Listen( int32 backlog )
{
	return m_net_handle->Listen( backlog );
}

EndpointPtr Endpoint::Accept()
{
	AddressPtr new_addr = new Address();
	NetHandlePtr new_handle = m_net_handle->Accept( new_addr );
	if ( NULL == new_handle )
		return NULL;

	new_handle->SetNonBlocking( true );
	new_handle->SetNoDelay( true );
	return (new Endpoint( new_addr, new_handle ));
}

Endpoint::operator SockFd() const
{
	return m_net_handle->Get();
}

Endpoint::operator std::string() const
{
	return m_addr->String();
}

}
