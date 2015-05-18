#include "timer.h"

#include "time/timer_manager.h"


Timer::Timer( uint32 interval, Handle handle, void* param, ETimerType type )
	: m_interval( interval )
	, m_counter( interval )
	, m_type( type )
	, m_status( TIMER_STATUS_IDLE )
	, m_handle( handle )
	, m_param( param )
{
}

Timer::~Timer()
{
	if ( TIMER_STATUS_ALIVE == m_status )
		Stop();
}

void Timer::Start()
{
	TimerManager::Instance().AddTimer( this );
}

void Timer::Stop()
{
	TimerManager::Instance().RemoveTimer( this );
}

void Timer::Reset( const uint32 interval )
{
	TimerManager::Instance().RemoveTimer( this );
	m_counter = m_interval = interval;
	TimerManager::Instance().AddTimer( this );
}
