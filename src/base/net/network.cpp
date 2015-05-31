#include "network.h"
#include "global.h"
#include "net/acceptor.h"
#include "thread/thread_pool.h"


namespace Net
{

Network::Network()
	: m_running( false )
{
	m_endpoint		= new Endpoint();
	m_event_poller	= EventPoller::Create();
}

Network::~Network()
{
}

bool Network::Init( std::string ip, uint16 port )
{
	return m_endpoint->Init( ip, port );
}

void Network::Start()
{
	if ( !m_endpoint->Valid() )
		return;

	if ( !m_endpoint->Bind() || !m_endpoint->Listen() )
		return;

	AcceptorPtr acceptor = new Acceptor( m_endpoint, this );
	m_event_poller->RegistInput( *(m_endpoint.Get()), acceptor );

	m_running = true;

	Thread::ThreadPool::Instance().Join( this );
}

void Network::RegisteClient( EndpointPtr endpoint )
{	
	m_client_endpoints[*(endpoint.Get())] = endpoint;
	LOG_DEBUG("new client [%s]", ((std::string)*(endpoint.Get())).c_str());
}

void Network::Stop()
{
	m_running = false;
}

void Network::Process()
{
	while ( m_running && Thread::ThreadPool::Instance().Running() )
		m_event_poller->ProcessPendingEvents( 1.0f );

	m_event_poller->DeregisterInput( *(m_endpoint.Get()) );
}

}
