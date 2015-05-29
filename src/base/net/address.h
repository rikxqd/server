#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include <string>
#include "public.h"
#include "utility/share_ptr.h"


namespace Net
{

class NetHandle;

class Address : public RefCounter
{
	friend class NetHandle;
public:
	Address();
	Address( uint16 port );
	Address( const char* ip, uint16 port );
	Address( uint32 ip, uint16 port );
	Address( const char* host );
	Address( SockAddr& addr );
	~Address();
      
public:
	uint16 Port() const;
	std::string IP() const;

	uint16 NetPort() const;
	uint32 NetIP() const;

	const SockAddr& Get() const;
	uint32 Length() const;

	std::string String() const;

private:
	SockAddr m_addr;
};

typedef SharePtr<Address> AddressPtr;

}/* end of Net */

#endif//_ADDRESS_H_
