#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include "public.h"

class Address
{
public:
      Address();
      Address( uint16 port );
      Address( std::string& ip, uint16 port );
      Address( uint16 ip, uint16 port );
      
      ~Address();
      
public:
      uint16 Port() const;
      std::string IP() const;
      
      uint16 NetPort() const;
      uint16 NetIP() const;
      
      const sockaddr& SockAddr() const;
      
      std::string String() const;
      
      void Set();
      void Set();
      void Set();
private:
      sockaddr addr;
};

#endif//_ADDRESS_H_
