#ifndef _EVENT_POLLER_H_
#define _EVENT_POLLER_H_

#include <map>
#include "public.h"
#include "utility/share_ptr.h"
#include "net/notify_handler.h"


namespace Net
{

class EventPoller : public RefCounter 
{
public:
	EventPoller();
	virtual ~EventPoller();

	static SharePtr<EventPoller> Create();

	bool RegistInput( int32 fd, InputNotifyHandlerPtr handler );
	bool RegistOutput( int32 fd, OutputNotifyHandlerPtr handler );

	bool DeregisterInput( int32 fd );
	bool DeregisterOutput( int32 fd );

	virtual int32 ProcessPendingEvents( double wait ) = 0;

protected:
	bool TriggerRead( int32 fd );
	bool TriggerWrite( int32 fd );

	virtual bool OnRegistInput( int32 fd ) = 0;
	virtual bool OnRegistOutput( int32 fd ) = 0;

	virtual bool OnDeregisterInput( int32 fd ) = 0;
	virtual bool OnDeregisterOutput( int32 fd ) = 0;

	int32 MaxFD() const;

private:
	std::map<int32, InputNotifyHandlerPtr> m_input_handlers;
	std::map<int32, OutputNotifyHandlerPtr> m_output_handlers;
};

typedef SharePtr<EventPoller> EventPollerPtr;

}/* end of Net */

#endif//_EVENT_POLLER_H_
