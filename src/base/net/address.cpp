#include "address.h"

#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netdb.h>

#include "utility/common.h"
#include "global.h"


namespace Net
{

Address::Address()
{
	::memset( &m_addr, 0x00, sizeof(m_addr) );
}

Address::Address( uint16 port )
{
	::memset( &m_addr, 0x00, sizeof(m_addr) );
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = htobe32( INADDR_ANY );
	m_addr.sin_port = htobe16( port );
}

Address::Address( const char* ip, uint16 port )
{
	::memset( &m_addr, 0x00, sizeof(m_addr) );
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htobe16( port );
	int32 res = ::inet_pton( AF_INET, ip, &m_addr.sin_addr );
	if ( 0 >= res )
		FATAL("ip is wrong");
}

Address::Address( uint32 ip, uint16 port )
{
	::memset( &m_addr, 0x00, sizeof(m_addr) );
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = htobe32( ip );
	m_addr.sin_port = htobe16( port );
}

static __thread char t_buf[64 * 1024] = {0};

Address::Address( const char* host )
{
	Common::Strings hosts;
	Common::Split( hosts, host, ':' );
	
	::memset( &m_addr, 0x00, sizeof(m_addr) );
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htobe16( atoi( hosts[1].c_str() ) );
		
	hostent hent;
	hostent* he = NULL;
  	int herrno = 0;
  	::memset( &hent, 0x00, sizeof(hent) );
	int res = gethostbyname_r( hosts[0].c_str(), &hent, t_buf, sizeof(t_buf), &he, &herrno );
	if ( 0 == res && NULL != he )
	{
		assert( AF_INET == he->h_addrtype && he->h_length == sizeof(uint32) );
		m_addr.sin_addr = *reinterpret_cast<in_addr*>( he->h_addr );
	}
	else if ( res )
		FATAL("host is wrong");
}

Address::Address( SockAddr& addr )
{
	::memset( &m_addr, 0x00, sizeof(m_addr) );
	::memcpy( &m_addr, &addr, sizeof(m_addr) );
}

Address::~Address()
{
}

uint16 Address::Port() const
{
	return be16toh( m_addr.sin_port );
}

std::string Address::IP() const
{
	char ip[32] = {0};
	assert( sizeof(ip) >= INET_ADDRSTRLEN );
	::inet_ntop( AF_INET, &m_addr.sin_addr, ip, static_cast<socklen_t>( sizeof(ip) ) );
	return ip;
}

uint16 Address::NetPort() const
{
	return m_addr.sin_port;
}

uint32 Address::NetIP() const
{
	return m_addr.sin_addr.s_addr;
}

const SockAddr& Address::Get() const
{
	return m_addr;
}

uint32 Address::Length() const
{
	return sizeof m_addr;
}

std::string Address::String() const
{
	char buf[32] = {0};
	snprintf( buf, sizeof(buf), "%s:%u", IP().c_str(), Port() );
	return buf;
}

}/* end of Net */
