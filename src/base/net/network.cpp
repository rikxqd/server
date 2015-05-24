#include "network.h"


namespace Net
{

Network::Network()
{
	m_endpoint = new Endpoint();
}

Network::~Network()
{
}

void Network::Init( string ip, uint16 port )
{
	m_endpoint->Init( ip, port );
}

void Network::Start()
{

}

EndpointPtr Network::Addr()
{
	return m_endpoint;
}

}
