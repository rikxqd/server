#ifndef _SERVER_APP_H_
#define _SERVER_APP_H_

#include "utility/share_ptr.h"
#include "net/network.h"


class ServerApp : public RefCounter
{
public:
	ServerApp();
	~ServerApp();

	bool Init( const char* ip, int32 port );

	void Start();

	void Stop();

private:
	Net::NetworkPtr			m_network;
};

typedef SharePtr<ServerApp> ServerAppPtr;

#endif//_SERVER_APP_H_

