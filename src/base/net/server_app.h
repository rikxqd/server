#ifndef _SERVER_APP_H_
#define _SERVER_APP_H_

#include "utility/share_ptr.h"
#include "thread/thread_pool.h"
#include "net/network.h"


class ServerApp : public RefCounter
{
public:
	ServerApp();
	~ServerApp();

	void Init( int argc, char* argv[] );

	void Start();

private:
	Thread::ThreadPoolPtr	m_pool;
	Net::NetworkPtr			m_network;
};

typedef SharePtr<ServerApp> ServerAppPtr;

#endif//_SERVER_APP_H_

