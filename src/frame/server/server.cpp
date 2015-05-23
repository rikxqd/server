#include "server.h"
#include "time/timer_manager.h"


Server::Server()
{
}

Server::~Server()
{
}

void Server::Init( int argc, char* argv[] )
{
	m_pool = new Thread::ThreadPool();
	m_network = new Net::Network();
	m_network->Init( "127.0.0.1", 3000 );
}

void Server::Start()
{
	m_pool->Start();
	TimerManager::Instance().Start( m_pool );
	m_network->Start();
}
