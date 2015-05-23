#include "endpoint.h"


namespace Net
{

Endpoint::Endpoint()
{
}

Endpoint::~Endpoint()
{
}

void Endpoint::Init( string ip, uint16 port )
{
	m_addr = new Address( port );
}

}
