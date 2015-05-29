#ifndef _NET_HANDLE_H_
#define _NET_HANDLE_H_

#include "utility/share_ptr.h"
#include "net/net_api.h"
#include "net/address.h"


namespace Net
{

class NetHandle : public RefCounter
{
public:
	NetHandle( SockFd sock );
	NetHandle( int32 domain, int32 type, int32 protocol );
	~NetHandle();

	SockFd Get() const;

	bool Valid() const;

	bool Bind( AddressPtr addr );

	bool Listen( int32 backlog );

	SharePtr<NetHandle> Accept( AddressPtr addr );

	int32 SetNonBlocking( bool non_blocking );

	int32 SetNoDelay( bool no_delay );

	bool Close();

private:
	SockFd	m_handle;
};

typedef SharePtr<NetHandle> NetHandlePtr;

}

#endif//_NET_HANDLE_H_

