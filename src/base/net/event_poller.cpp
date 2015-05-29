#include "event_poller.h"
#include "net/select_poller.h"


namespace Net
{

EventPoller::EventPoller()
{
}

EventPoller::~EventPoller()
{
}

EventPollerPtr EventPoller::Create()
{
	return new SelectPoller();
}

bool EventPoller::RegistInput( int32 fd, InputNotifyHandlerPtr handler )
{
	if ( !this->OnRegistInput( fd ) )
		return false;

	m_input_handlers[fd] = handler;
	return true;
}

bool EventPoller::RegistOutput( int32 fd, OutputNotifyHandlerPtr handler )
{
	if ( !this->OnRegistOutput( fd ) )
		return false;

	m_output_handlers[fd] = handler;
	return true;
}

bool EventPoller::DeregisterInput( int32 fd )
{
	m_input_handlers.erase( fd );
	return OnDeregisterInput( fd );
}

bool EventPoller::DeregisterOutput( int32 fd )
{
	m_output_handlers.erase( fd );
	return OnDeregisterOutput( fd );
}

bool EventPoller::TriggerRead( int32 fd )
{
	std::map<int32, InputNotifyHandlerPtr>::iterator it = m_input_handlers.find( fd );
	if ( it == m_input_handlers.end() )
		return false;

	it->second->HandleInputNotify( fd );
	return true;
}

bool EventPoller::TriggerWrite( int32 fd )
{
	std::map<int32, OutputNotifyHandlerPtr>::iterator it = m_output_handlers.find( fd );
	if ( it == m_output_handlers.end() )
		return false;

	it->second->HandleOutputNotify( fd );
	return true;
}

int32 EventPoller::MaxFD() const
{
	int max = -1;

	{
		std::map<int32, InputNotifyHandlerPtr>::const_reverse_iterator crit = m_input_handlers.crbegin();
		if ( crit != m_input_handlers.crend() )
			max = crit->first;
	}

	{
		std::map<int32, OutputNotifyHandlerPtr>::const_reverse_iterator crit = m_output_handlers.crbegin();
		if ( crit != m_output_handlers.crend() && max < crit->first )
			max = crit->first;
	}

	return max;
}

}/* end of Net */
