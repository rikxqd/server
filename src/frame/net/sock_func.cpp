#include "sock_func.h"

#include <sys/socket.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>

#include "global.h"


namespace SockFunc
{

SOCKFD Socket( int32 domain, int32 type, int32 protocol )
{
	SOCKFD ssock = socket( domain, type, protocol );
	if ( 0 > ssock )
		FATAL( "create socket fail " );
	return ssock;
}

int32 Connect( int32 sockfd, const sockaddr* addr, socklen_t addrlen )
{
	int32 res = connect( sockfd, addr, addrlen );
	if ( 0 > res )
		FATAL( "connect fail " );
	return res;
}

int32 Bind( int32 sockfd, const sockaddr* sa, socklen_t salen )
{
	int32 res = bind( sockfd, sa, salen );
	if ( 0 > res )
		FATAL( "bind fail " );
	return res;
}

int32 Listen( int32 sockfd, int32 backlog )
{
	const char* env = getenv("LISTENQ"); // 获取环境变量
	if ( NULL != env )
		backlog = atoi(env);
	int32 res = listen( sockfd, backlog );
	if ( 0 > res )
		FATAL( "listen fail " );
	return res;
}

SOCKFD Accept( int32 sockfd, sockaddr* sa, socklen_t* len )
{
	SOCKFD csock = 0;
	while ( true )
	{
		csock = accept( sockfd, sa, len );
		if ( 0 <= csock )
			break;
	      
#ifdef EPROTO
		if ( EPROTO == errno || ECONNABORTED == errno )
#else
		if ( ECONNABORTED == errno )
#endif
			FATAL( "accept again " );
		else
		{
			FATAL( "accept fail " );
			break;
		}
	}
	return csock;
}

}/* end of SockFunc */

/*
void Getpeername(int32 fd, sockaddr *sa, socklen_t *salenptr)
{
	if (getpeername(fd, sa, salenptr) < 0)
		err_sys("getpeername error");
}

void Getsockname(int32 fd, sockaddr *sa, socklen_t *salenptr)
{
	if (getsockname(fd, sa, salenptr) < 0)
		err_sys("getsockname error");
}

void Getsockopt(int32 fd, int32 level, int32 optname, void *optval, socklen_t *optlenptr)
{
	if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
		err_sys("getsockopt error");
}

#ifdef	HAVE_INET6_RTH_INIT
int32 Inet6_rth_space(int32 type, int32 segments)
{
	int32 ret;
	
	ret = inet6_rth_space(type, segments);
	if (ret < 0)
		err_quit("inet6_rth_space error");

	return ret;
}

void* Inet6_rth_init(void *rthbuf, socklen_t rthlen, int32 type, int32 segments)
{
	void *ret;

	ret = inet6_rth_init(rthbuf, rthlen, type, segments);
	if (ret == NULL)
		err_quit("inet6_rth_init error");

	return ret;
}

void Inet6_rth_add(void *rthbuf, const struct in6_addr *addr)
{
	if (inet6_rth_add(rthbuf, addr) < 0)
		err_quit("inet6_rth_add error");
}

void Inet6_rth_reverse(const void *in, void *out)
{
	if (inet6_rth_reverse(in, out) < 0)
		err_quit("inet6_rth_reverse error");
}

int32 Inet6_rth_segments(const void *rthbuf)
{
	int32 ret;

	ret = inet6_rth_segments(rthbuf);
	if (ret < 0)
		err_quit("inet6_rth_segments error");

	return ret;
}

struct in6_addr* Inet6_rth_getaddr(const void *rthbuf, int32 idx)
{
	struct in6_addr *ret;

	ret = inet6_rth_getaddr(rthbuf, idx);
	if (ret == NULL)
		err_quit("inet6_rth_getaddr error");

	return ret;
}
#endif

#ifdef HAVE_KQUEUE
int32 Kqueue()
{
	int32 ret;

	if ((ret = kqueue()) < 0)
		err_sys("kqueue error");
	return ret;
}

int32 Kevent(int32 kq, const struct kevent *changelist, int32 nchanges, struct kevent *eventlist, int32 nevents, const struct timespec *timeout)
{
	int32 ret;

	if ((ret = kevent(kq, changelist, nchanges,
					  eventlist, nevents, timeout)) < 0)
		err_sys("kevent error");
	return ret;
}
#endif

#ifdef	HAVE_POLL
int32 Poll(struct pollfd *fdarray, unsigned long nfds, int32 timeout)
{
	int32		n;

	if ( (n = poll(fdarray, nfds, timeout)) < 0)
		err_sys("poll error");

	return(n);
}
#endif

ssize_t Recv(int32 fd, void *ptr, size_t nbytes, int32 flags)
{
	ssize_t		n;

	if ( (n = recv(fd, ptr, nbytes, flags)) < 0)
		err_sys("recv error");
	return(n);
}

ssize_t Recvfrom(int32 fd, void *ptr, size_t nbytes, int32 flags, sockaddr *sa, socklen_t *salenptr)
{
	ssize_t		n;

	if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
		err_sys("recvfrom error");
	return(n);
}

ssize_t Recvmsg(int32 fd, struct msghdr *msg, int32 flags)
{
	ssize_t		n;

	if ( (n = recvmsg(fd, msg, flags)) < 0)
		err_sys("recvmsg error");
	return(n);
}

int32 Select(int32 nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
	int32		n;

	if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
		err_sys("select error");
	return(n);
}

void Send(int32 fd, const void *ptr, size_t nbytes, int32 flags)
{
	if (send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
		err_sys("send error");
}

void Sendto(int32 fd, const void *ptr, size_t nbytes, int32 flags, const sockaddr *sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
		err_sys("sendto error");
}

void Sendmsg(int32 fd, const struct msghdr *msg, int32 flags)
{
	unsigned int32	i;
	ssize_t			nbytes;

	nbytes = 0;	
	for (i = 0; i < msg->msg_iovlen; i++)
		nbytes += msg->msg_iov[i].iov_len;

	if (sendmsg(fd, msg, flags) != nbytes)
		err_sys("sendmsg error");
}

void Setsockopt(int32 fd, int32 level, int32 optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(fd, level, optname, optval, optlen) < 0)
		err_sys("setsockopt error");
}

void Shutdown(int32 fd, int32 how)
{
	if (shutdown(fd, how) < 0)
		err_sys("shutdown error");
}

int32 Sockatmark(int32 fd)
{
	int32		n;

	if ( (n = sockatmark(fd)) < 0)
		err_sys("sockatmark error");
	return(n);
}

void Socketpair(int32 family, int32 type, int32 protocol, int32 *fd)
{
	int32		n;

	if ( (n = socketpair(family, type, protocol, fd)) < 0)
		err_sys("socketpair error");
}
*/