#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include <string>
#include <netinet/in.h>
#include "public.h"


class Address
{
public:
	Address();
	explicit Address( uint16 port );
	Address( string& ip, uint16 port );
	Address( uint32 ip, uint16 port );
	Address( string& host );
      
	~Address();
      
public:
	uint16 Port() const;
	string IP() const;

	uint16 NetPort() const;
	uint32 NetIP() const;

	const sockaddr_in& SockAddr() const;

	string String() const;

	void Set( uint16 port );
	void Set( string& ip, uint16 port );
	void Set( uint16 ip, uint16 port );
	void Set( sockaddr_in& addr );

private:
	sockaddr_in addr;
};

#endif//_ADDRESS_H_
