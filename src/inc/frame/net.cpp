#include "net.h"
#include <arpa/inet.h>

bool Net::Init( const char* ip, uint16 port )
{
	m_socket = Socket( AF_INET, SOCK_STREAM, 0 );
	if ( 0 > m_socket )
		return false;

	struct sockaddr_in saddr= {0};
	saddr.sin_family        = AF_INET;
	saddr.sin_port          = htons( port );
	saddr.sin_addr.s_addr	= inet_addr( ip );

	int32 res = Bind( m_socket, (Address*)&saddr, sizeof saddr );
	if ( 0 > res )
		return false;

	res = Listen( m_socket, 1024 );
	if ( 0 > res )
		return false;

	m_status = E_NetStatus_Init;
	return true;
}