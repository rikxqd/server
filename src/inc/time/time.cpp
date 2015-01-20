#include "time.h"

#include <time.h>
#ifdef WIN32
	
#elif UNIX
#include <unistd.h>
#endif


Time::Time()
	: m_is_cumulation( 0 )
	, m_cumulation( false )
{
	m_time = 0;
	CasheTime();
	m_zone_second = m_hour * 3600 + m_minute * 60 + m_second;

	m_time = static_cast< int32 >( time( 0 ) );
	CasheClock();
	CasheTime();
}

Time::~Time()
{
}


void Time::SleepMsec( int64 msec )
{
#ifdef WIN32
	Sleep( msec );
#elif UNIX
	usleep( msec * 1000 );
#endif
}

void Time::Refresh()
{
	int64 pass = m_pass;
	CasheClock();

#if WIN32
	if ( m_pass < pass )
	{
		std::cout << "Time Cycle." << std::endl;
		return;
	}
#endif

	if ( m_is_cumulation )
	{
		std::cout << m_pass - pass << std::endl;
		m_cumulation += (m_pass - pass);
		int32 sec = static_cast< int32 >( m_cumulation / 1000 );
		if ( sec )
		{
			m_time += sec;
			m_cumulation = m_cumulation % 1000;
			CasheTime();
		}
	}
}

int32 Time::Year()
{
	return m_year;
}	

int32 Time::Month() 
{
	return m_month;
}
int32 Time::Day() 
{
	return m_day;
}	
int32 Time::Hour() 
{
	return m_hour;
}
int32 Time::Minute() 
{
	return m_minute;
}
int32 Time::Second() 
{
	return m_second;
}
int32 Time::WeekDay()
{
	return m_wday;
}
int32 Time::YeayDay() 
{
	return m_yday;
}
int32 Time::Seconds() 
{
	return m_time;
}
int32 Time::Minutes() 
{
	return m_time / 60;
}

void Time::Abjust( int32 time )
{
	if (time)
	{
		m_time = time;
		m_is_cumulation = true;
	}
	else
		m_is_cumulation = false;
}

void Time::CasheClock()
{
#ifdef WIN32
	m_pass = static_cast< int64 >( clock() );
#elif UNIX
	timespec ts;
	clock_gettime( CLOCK_MONOTONIC, &ts );
	m_pass = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#endif
}

void Time::CasheTime()
{
	time_t time = static_cast< time_t >( m_time );
	tm* local = localtime( &time );
	this->m_year	= local->tm_year + 1900;
	this->m_month	= local->tm_mon + 1;
	this->m_day		= local->tm_mday;
	this->m_hour	= local->tm_hour;
	this->m_minute	= local->tm_min;
	this->m_second	= local->tm_sec;
	this->m_wday	= local->tm_wday;
	this->m_yday	= local->tm_yday;
}
