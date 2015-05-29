#include "select_poller.h"


namespace Net
{

SelectPoller::SelectPoller()
	: m_largest_fd( -1 )
	, m_write_fd_count( 0 )
{
}

SelectPoller::~SelectPoller()
{
}

bool SelectPoller::OnRegistInput( int32 fd )
{
#ifdef WIN32
	if ( FD_SETSIZE <= m_read_set.fd_count )
		return false;
#elif UNIX
	if ( 0 > fd || FD_SETSIZE <= fd )
		return false;
#endif

	if ( FD_ISSET( fd, &m_read_set ) )
		return false;

	FD_SET( fd, &m_read_set );

	if (fd > m_largest_fd)
		m_largest_fd = fd;

	return true;
}

bool SelectPoller::OnRegistOutput( int32 fd )
{
#ifdef WIN32
	if ( FD_SETSIZE <= m_write_set.fd_count )
		return false;
#elif UNIX
	if ( 0 > fd || FD_SETSIZE <= fd )
		return false;
#endif
	if ( FD_ISSET( fd, &m_write_set ) )
		return false;

	FD_SET(fd, &m_write_set);

	if ( fd > m_largest_fd )
		m_largest_fd = fd;

	++m_write_fd_count;
	return true;
}

bool SelectPoller::OnDeregisterInput( int32 fd )
{
#ifdef UNIX
	if ( 0 > fd || FD_SETSIZE <= fd )
		return false;
#endif

	if ( !FD_ISSET( fd, &m_read_set ) )
		return false;

	FD_CLR( fd, &m_read_set );

	if ( fd == m_largest_fd )
		m_largest_fd = MaxFD();

	return true;
}

bool SelectPoller::OnDeregisterOutput( int32 fd )
{
#ifdef UNIX
	if ( 0 > fd || FD_SETSIZE <= fd )
		return false;
#endif

	if (!FD_ISSET(fd, &m_write_set))
		return false;

	FD_CLR(fd, &m_write_set);

	if (fd == m_largest_fd)
		m_largest_fd = MaxFD();

	--m_write_fd_count;
	return true;
}

int32 SelectPoller::ProcessPendingEvents( double wait )
{
	fd_set	read_set;
	fd_set	write_set;
	
	FD_ZERO( &write_set );
	FD_ZERO( &write_set );

	read_set = m_read_set;
	write_set = m_write_set;

	struct timeval timeout;
	timeout.tv_sec = (int32)wait;
	timeout.tv_usec = (int32)((wait - (double)timeout.tv_sec) * 1000000.0);

	int32 count = 0;

#ifdef WIN32
	if (m_largest_fd == -1)
		Time::SleepMsec( (int64)(wait * 1000.0) );
	else
#endif
	{
		count = select( m_largest_fd + 1, &read_set, (m_write_fd_count ? &write_set : NULL), NULL, &timeout );
	}

	if ( 0 < count )
		this->HandleEvents( count, read_set, write_set);
	else if ( -1 == count )
	{
		
	}

	return count;
}

void SelectPoller::HandleEvents( int32& count, fd_set& read_set, fd_set& write_set )
{
#ifdef WIN32
	for ( uint32 i = 0 ; i < read_set.fd_count ; ++i )
	{
		int32 fd = read_set.fd_array[i];
		--count;
		TriggerRead(fd);
	}

	for ( uint32 i = 0 ; i < write_set.fd_count ; ++i )
	{
		int32 fd = write_set.fd_array[i];
		--count;
		TriggerWrite(fd);
	}
#elif UNIX
	for ( int32 fd = 0; fd <= m_largest_fd && count > 0; ++fd )
	{
		if ( FD_ISSET( fd, &read_set ) )
		{
			--count;
			TriggerRead(fd);
		}

		if ( FD_ISSET( fd, &write_set ) )
		{
			--count;
			TriggerWrite(fd);
		}
	}
#endif
}

}/* end of Net */
