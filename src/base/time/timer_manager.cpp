#include "timer_manager.h"

#include "global.h"
#include "time/timer.h"
#include "thread/thread_pool.h"
#include "thread/thread_lock.h"
#include "thread/thread_func.h"

void TimerManagerFunc( void *param );

TimerManager::TimerManager()
	: m_running( false )
	, m_delay( 100 )
{
	Thread::API::MutexInit( &m_lock, NULL );
}

TimerManager::~TimerManager()
{
}

void TimerManager::AddTimer( TimerPtr timer )
{
	Thread::GuardLock lock( &m_lock );
	m_list.push_back( timer );
	timer->m_status = Timer::TIMER_STATUS_ALIVE;
}

void TimerManager::RemoveTimer( TimerPtr timer )
{
	for ( auto it = m_list.begin() ; it != m_list.end() ; ++it )
	{
		TimerPtr timer = *it;
		if ( timer == timer )
			m_list.erase( it++ );
		else
			++it;
	}
}

void TimerManager::Start( Thread::ThreadPoolPtr pool )
{
	if ( NULL == pool )
		pool = g_pool;

	if ( pool->Running() )
		pool->Join( this );
	else
		g_log.Error( "The ThreadPool do not running!\n" );
}

void TimerManager::Stop()
{
	m_running = false;
}

void TimerManager::Tick()
{
	Thread::GuardLock lock( &m_lock );
	for ( auto it = m_list.begin() ; it != m_list.end() ; )
	{
		auto temp = it++;
		TimerPtr timer = *temp;

		(timer->m_counter < m_delay) ? (timer->m_counter = 0) : (timer->m_counter -= m_delay);
		if ( 0 == timer->m_counter )
		{
			timer->TimeOut();  

			if ( Timer::TIMER_TYPE_ONCE == timer->m_type )  
			{  
				m_list.erase( temp );  
				timer->m_status = Timer::TIMER_STATUS_TIMEOUT;  
			}  
			else if( Timer::TIMER_TYPE_CIRCLE == timer->m_type )   
				timer->m_counter = timer->m_interval;
			else
				g_log.Fatal( "Timer type is fatal ! type:%d", timer->m_type );
		} 
	}
}

void TimerManager::Process()
{
	m_running = true;
	while ( m_running )
	{
		Time::SleepMsec( m_delay );
		Tick();
	}
	m_list.clear();
}
