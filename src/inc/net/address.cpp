#include "address.h"

#include <strings.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netdb.h>


Address::Address()
{
	::bzero( &addr, sizeof(addr) );
}

Address::Address( uint16 port )
{
	::bzero( &addr, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htobe32( INADDR_ANY );
	addr.sin_port = htobe16( port );
}

Address::Address( string& ip, uint16 port )
{
	::bzero( &addr, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_port = htobe16( port );
	int32 res = ::inet_pton( AF_INET, ip.c_str(), &addr.sin_addr );
	if ( 0 >= res )
		cout << "ip is wrong" << endl;
}

Address::Address( uint32 ip, uint16 port )
{
	::bzero( &addr, sizeof(addr) );
}

static __thread char t_buf[64 * 1024] = {0};

Address::Address( string& host )
{
	size_t index = host.find_last_of(":");
	string h_port = host.substr( index + 1, host.length() );
	string h_name = host.substr( 0, index );	
	
	::bzero( &addr, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_port = htobe16( atoi( h_port.c_str() ) );
		
	hostent hent;
	hostent* he = NULL;
  	int herrno = 0;
  	bzero( &hent, sizeof(hent) );
	int res = gethostbyname_r( h_name.c_str(), &hent, t_buf, sizeof(t_buf), &he, &herrno );
	if ( 0 == res && NULL != he )
	{
		assert( AF_INET == he->h_addrtype && he->h_length == sizeof(uint32) );
		addr.sin_addr = *reinterpret_cast<in_addr*>( he->h_addr );
	}
	else if ( res )
		cout << "host is wrong" << endl;
}

Address::~Address()
{

}

uint16 Address::Port() const
{
	return be16toh( addr.sin_port );
}

string Address::IP() const
{
	char ip[32] = {0};
	assert( sizeof(ip) >= INET_ADDRSTRLEN );
	::inet_ntop( AF_INET, &addr.sin_addr, ip, static_cast<socklen_t>( sizeof(ip) ) );
	return ip;
}

uint16 Address::NetPort() const
{
	return addr.sin_port;
}

uint32 Address::NetIP() const
{
	return addr.sin_addr.s_addr;
}

const sockaddr_in& Address::SockAddr() const
{
	return addr;
}

string Address::String() const
{
	char buf[32] = {0};
	snprintf( buf, sizeof(buf), "%s:%u", IP().c_str(), Port() );
	return buf;
}

void Address::Set( uint16 port )
{

}
void Address::Set( string& ip, uint16 port )
{

}
void Address::Set( uint16 ip, uint16 port )
{

}
void Address::Set( sockaddr_in& addr )
{

}
