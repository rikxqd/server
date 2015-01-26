#include "timer_manager.h"

#include "global.h"
#include "time/timer.h"


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

void TimerManager::AddTimer( Timer* timer )
{
	m_list.push_back( timer );
}

void TimerManager::RemoveTimer( Timer* timer )
{
	for ( auto it = m_list.begin() ; it != m_list.end() ; ++it )
	{
		if ( timer == *it )
			m_list.erase( it++ );
		else
			++it;
	}
}

void TimerManager::Start()
{
	Time::SleepMsec( 2000 );
	g_thread_pool.Join( TimerManagerFunc, this );
}

void TimerManager::Stop()
{
	m_start = false;
}

void TimerManager::Tick()
{
	for ( auto it = m_list.begin() ; it != m_list.end() ; )
	{
		auto temp = it++;
		Timer* timer = *temp;

		(timer->m_counter < m_delay) ? (timer->m_counter = 0) : (timer->m_counter -= m_delay);
		if ( 0 == timer->m_counter )
		{
			if ( timer->m_handle )  
				timer->m_handle(timer,timer->m_param);  

			if ( Timer::TIMER_ONCE == timer->m_type )  
			{  
				m_list.erase( temp );  
				timer->m_status = Timer::TIMER_TIMEOUT;  
			}  
			else if( Timer::TIMER_CIRCLE == timer->m_type )   
				timer->m_counter = timer->m_interval;
			else
				FATAL( "timer type is fatal ! type:%d", timer->m_type );
		} 
	}
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
