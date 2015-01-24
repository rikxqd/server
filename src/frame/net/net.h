#ifndef _NET_H_
#define _NET_H_

#include "net/sock_func.h"


class Net
{
public:
	enum E_NetStatus
	{
		E_NetStatus_Default	= 0,
		E_NetStatus_Init	= 1,
		E_NetStatus_Runing	= 2,
		E_NetStatus_End,
	};

	typedef void* ( *AcceptHandle )( void* );

	Net();
	~Net();

	bool Init( const char* ip, uint16 port );

	void Handle( AcceptHandle handle );

	void Run();

private:
	SOCKFD			m_socket;
	E_NetStatus		m_status;
	AcceptHandle	m_accept_handle;
};

#endif//_NET_H_

