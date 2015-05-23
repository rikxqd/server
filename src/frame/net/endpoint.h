#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_

#include "utility/share_ptr.h"
#include "net/address.h"


namespace Net
{

class Endpoint : public RefCounter
{
public:
	Endpoint();
	~Endpoint();

	void Init( string ip, uint16 port );

private:
	AddressPtr	m_addr;
};

typedef SharePtr<Endpoint> EndpointPtr;

}

#endif//_ENDPOINT_H_

