#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_

#include "utility/share_ptr.h"
#include "net/address.h"
#include "net/net_handle.h"


namespace Net
{

class Endpoint : public RefCounter
{
public:
	Endpoint();
	Endpoint( AddressPtr addr, NetHandlePtr net_handle );
	~Endpoint();

	bool Valid() const;

	bool Init( std::string ip, uint16 port );

	bool Bind();

	bool Listen( int32 backlog = 5 );

	SharePtr<Endpoint> Accept();

	operator SockFd() const;
	operator std::string() const;

private:
	AddressPtr		m_addr;
	NetHandlePtr	m_net_handle;
};

typedef SharePtr<Endpoint> EndpointPtr;

}

#endif//_ENDPOINT_H_

