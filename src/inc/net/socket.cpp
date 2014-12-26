#include "socket.h"
#include <sys/socket.h>

SOCKFD Socket( int32 domain, int32 type, int32 protocol )
{
      return socket( domain, type, protocol );
}