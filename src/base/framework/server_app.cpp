#include "server_app.h"
#include "thread/thread_api.h"
#include "thread/thread_pool.h"


ServerApp::ServerApp()
{
	m_network = new Net::Network();
}

ServerApp::~ServerApp()
{
	Thread::API::ThreadJoin( Thread::ThreadPool::Instance().Key(), NULL );
}

bool ServerApp::Init( const char* ip, int32 port )
{
	return m_network->Init( ip, port );
}

void ServerApp::Start()
{
	m_network->Start();
}

void ServerApp::Stop()
{
	m_network->Stop();
}
