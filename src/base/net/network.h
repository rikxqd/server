#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "utility/share_ptr.h"
#include "net/endpoint.h"


namespace Net
{

class Network : public RefCounter
{
public:
	Network();
	~Network();

	void Init( string ip, uint16 port );

	void Start();

	EndpointPtr Addr();

private:
	EndpointPtr	m_endpoint;
};

typedef SharePtr<Network> NetworkPtr;

}

#endif//_NETWORK_H_

