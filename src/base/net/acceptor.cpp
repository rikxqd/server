#include "acceptor.h"


namespace Net
{

Acceptor::Acceptor( EndpointPtr endpoint, NetworkPtr network )
	: m_endpoint( endpoint )
	, m_network( network )
{
}

Acceptor::~Acceptor()
{
}

bool Acceptor::HandleInputNotify( int32 fd )
{
	int32 tickcount = 0;
	while ( tickcount++ < 256 )
	{
		EndpointPtr new_endpoint = m_endpoint->Accept();
		if ( NULL == new_endpoint )
		{
			if ( 1 == tickcount )
			{
				// TODO
			}
			break;
		}
		else
		{
			m_network->RegisteClient( new_endpoint );
		}
	}
	return true;
}

}/* end of Net */
