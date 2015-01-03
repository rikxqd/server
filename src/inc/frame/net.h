#ifndef _NET_H_
#define _NET_H_

#include "net/warp_socket.h"


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

	Net();
	~Net();

	bool Init( const char* ip, uint16 port );
private:
	SOCKFD		m_socket;
	E_NetStatus	m_status;
};

#endif//_NET_H_

