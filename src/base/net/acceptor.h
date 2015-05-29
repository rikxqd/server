#ifndef _ACCEPTOR_H_
#define _ACCEPTOR_H_

#include "utility/share_ptr.h"
#include "net/notify_handler.h"
#include "net/endpoint.h"
#include "net/network.h"


namespace Net
{

class Acceptor : public InputNotifyHandler
{
public:
	Acceptor( EndpointPtr endpoint, NetworkPtr	network );
	virtual ~Acceptor();

	virtual bool HandleInputNotify( int32 fd );

private:
	EndpointPtr	m_endpoint;
	NetworkPtr	m_network;
};

typedef SharePtr<Acceptor> AcceptorPtr;

}/* end of Net */

#endif//_ACCEPTOR_H_
