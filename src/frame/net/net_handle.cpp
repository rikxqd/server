#include "net_handle.h"


namespace Net
{

NetHandle::NetHandle()
{
}

NetHandle::~NetHandle()
{
}

void NetHandle::Init( int32 domain, int32 type, int32 protocol )
{
	m_handle = SockFunc::Socket( AF_INET, SOCK_STREAM, 0 );
}

}
