#include "address.h"

#include <strings.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>


Address::Address()
{
	::bzero( &addr, sizeof addr );
}

Address::Address( uint16 port )
{
	::bzero( &addr, sizeof addr );
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htobe32( INADDR_ANY );
	addr.sin_port = htobe16( port );
}

Address::Address( string& ip, uint16 port )
{
	::bzero( &addr, sizeof addr );
	addr.sin_family = AF_INET;
	addr.sin_port = htobe16( port );
	int32 res = ::inet_pton( AF_INET, ip.c_str(), &addr.sin_addr );
	if ( 0 >= res )
		cout << "ip is wrong" << endl;
}

Address::Address( uint32 ip, uint16 port )
{
	::bzero( &addr, sizeof addr );
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
	char ip[32];
	size_t size = sizeof ip;
	assert( size >= INET_ADDRSTRLEN );
	::inet_ntop( AF_INET, &addr.sin_addr, ip, static_cast<socklen_t>(size) );
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
	char buf[32];
	snprintf( buf, sizeof buf, "%s:%u", IP().c_str(), Port() );
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
