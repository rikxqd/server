#include "endpoint.h"


namespace Net
{

Endpoint::Endpoint()
{
}

Endpoint::~Endpoint()
{
}

bool Endpoint::Init( string ip, uint16 port )
{
	m_addr = new Address( ip.c_str(), port );
	m_net_handle = new NetHandle( AF_INET, SOCK_STREAM, 0 );
	if ( m_net_handle->Bind( m_addr ) && m_net_handle->Listen() )
		return false;

	return true;
}

}
