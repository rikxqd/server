#include "socket.h"

SOCKFD Socket( int domain, int type, int protocol )
{
      return socket( domain, type, protocol );
}