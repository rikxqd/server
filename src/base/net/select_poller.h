#ifndef _SELECT_POLLER_H_
#define _SELECT_POLLER_H_

#include "public.h"
#include "utility/share_ptr.h"
#include "net/event_poller.h"


namespace Net
{

class SelectPoller : public EventPoller
{
public:
	SelectPoller();
	virtual ~SelectPoller();

	virtual bool OnRegistInput( int32 fd );
	virtual bool OnRegistOutput( int32 fd );

	virtual bool OnDeregisterInput( int32 fd );
	virtual bool OnDeregisterOutput( int32 fd );

	virtual int32 ProcessPendingEvents( double wait );

protected:
	void HandleEvents( int32& count, fd_set& read_set, fd_set& write_set );

private:
	fd_set	m_read_set;
	fd_set	m_write_set;
	int		m_largest_fd;// 最后注册的socket描述符 （读或写）
	int		m_write_fd_count;// 注册写的socket描述符数量
};

typedef SharePtr<SelectPoller> SelectPollerPtr;

}/* end of Net */

#endif//_SELECT_POLLER_H_
