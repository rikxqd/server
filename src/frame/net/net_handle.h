#ifndef _NET_HANDLE_H_
#define _NET_HANDLE_H_

#include "utility/share_ptr.h"
#include "net/sock_func.h"


namespace Net
{

class NetHandle : public RefCounter
{
public:
	NetHandle();
	~NetHandle();

	void Init( int32 domain, int32 type, int32 protocol );

private:
	SOCKFD m_handle;
};

typedef SharePtr<NetHandle> NetHandlePtr;

}

#endif//_NET_HANDLE_H_

