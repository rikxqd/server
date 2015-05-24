#include "server_app.h"
#include "time/timer_manager.h"


ServerApp::ServerApp()
{
	m_pool = new Thread::ThreadPool();
	m_network = new Net::Network();
}

ServerApp::~ServerApp()
{
}

void ServerApp::Init( int argc, char* argv[] )
{
	m_network->Init( "127.0.0.1", 3000 );
}

void ServerApp::Start()
{
	m_pool->Start();
	TimerManager::Instance().Start( m_pool );
	m_network->Start();
}
