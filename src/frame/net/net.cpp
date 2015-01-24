#include "net.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <pthread.h>

Net::Net()
	: m_socket( 0 )
	, m_status( E_NetStatus_Default )
	, m_accept_handle( NULL )
{
}

Net::~Net()
{
}

bool Net::Init( const char* ip, uint16 port )
{
	m_socket = SockFunc::Socket( AF_INET, SOCK_STREAM, 0 );
	if ( 0 > m_socket )
		return false;

	struct sockaddr_in saddr= {0};
	saddr.sin_family        = AF_INET;
	saddr.sin_port          = htons( port );
	saddr.sin_addr.s_addr	= inet_addr( ip );

	int32 res = SockFunc::Bind( m_socket, (sockaddr*)&saddr, sizeof saddr );
	if ( 0 > res )
		return false;

	res = SockFunc::Listen( m_socket, 1024 );
	if ( 0 > res )
		return false;

	m_status = E_NetStatus_Init;
	return true;
}

void Net::Handle( AcceptHandle handle )
{
	m_accept_handle = handle;
}

void Net::Run()
{
	if ( m_accept_handle )
	{
		pthread_t tid;
		pthread_create( &tid, NULL, m_accept_handle, NULL );
	}
}