#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include <string>
#include "public.h"
#include "utility/share_ptr.h"


namespace Net
{

class Address : public RefCounter
{
public:
	Address();
	Address( uint16 port );
	Address( string& ip, uint16 port );
	Address( uint32 ip, uint16 port );
	Address( string& host );
	~Address();
      
public:
	uint16 Port() const;
	string IP() const;

	uint16 NetPort() const;
	uint32 NetIP() const;

	const SockAddress& SockAddr() const;

	string String() const;

private:
	SockAddress m_addr;
};

typedef SharePtr<Address> AddressPtr;

}

#endif//_ADDRESS_H_
