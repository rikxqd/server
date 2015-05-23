#ifndef _SERVER_H_
#define _SERVER_H_

#include "thread/thread_pool.h"
#include "net/network.h"


class Server
{
public:
	Server();
	~Server();

	void Init( int argc, char* argv[] );

	void Start();

private:
	Thread::ThreadPoolPtr	m_pool;
	Net::NetworkPtr			m_network;
};

#endif//_SERVER_H_

