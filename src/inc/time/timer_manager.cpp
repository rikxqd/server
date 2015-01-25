#include "timer_manager.h"

#include "global.h"


void TimerManagerFunc( void *param );

TimerManager::TimerManager()
	: m_start( false )
	, m_delay( 1 )
{
	pthread_mutex_init( &m_t_mutex, NULL );
}

TimerManager::~TimerManager()
{
}

bool TimerManager::AddTimer( Timer* timer )
{
	for ( auto it : m_list )
		if ( it == timer )
			return false;

	m_list.push_back( timer );
	return true;
}

bool TimerManager::RemoveTimer( Timer* timer )
{
	for ( auto it = m_list.begin() ; it != m_list.end() ; ++it )
		if ( *it == timer )
		{
			it = m_list.erase( it );
			return true;
		}

	return false;
}

void TimerManager::Start()
{
	g_thread_pool.Join( TimerManagerFunc, this );
}

void TimerManager::Stop()
{
	m_start = false;
}

void TimerManager::Tick()
{

}

void TimerManagerFunc( void *param )
{
	TimerManager* mgr = static_cast< TimerManager* >( param );
	if ( !mgr )
		return;

	mgr->m_start = true;
	while ( mgr->m_start )
	{
		Time::SleepMsec( mgr->m_delay );
		mgr->Tick();
	}
}
