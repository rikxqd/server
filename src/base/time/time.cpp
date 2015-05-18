#include "time.h"

#include <time.h>
#ifdef WIN32
	
#elif UNIX
#include <unistd.h>
#endif


Time::Time()
	: m_is_tick( false )
	, m_tick_cache( 0 )
{
	m_utc_time = 0;
	CasheTime();
	m_zone_second = m_hour * 3600 + m_minute * 60 + m_second;

	m_utc_time = static_cast< int64 >( time( 0 ) );
	CasheClock();
	CasheTime();
}

Time::~Time()
{
}


void Time::SleepMsec( int64 msec )
{
#ifdef WIN32
	::Sleep( msec );
#elif UNIX
	::usleep( msec * 1000 );
#endif
}

void Time::Refresh()
{
	int64 cpu_clock = m_cpu_clock;
	CasheClock();

#if WIN32
	if ( m_cpu_clock < cpu_clock )
	{
		std::cout << "Time Cycle." << std::endl;
		return;
	}
#endif

	if ( m_is_tick )
	{
		m_tick_cache += m_cpu_clock - cpu_clock;
		int64 sec = static_cast< int64 >( m_tick_cache / 1000 );
		if ( sec )
		{
			m_utc_time += sec;
			m_tick_cache = m_tick_cache % 1000;
			CasheTime();
		}
	}
}

int32 Time::Year() const
{
	return m_year;
}	

int32 Time::Month() const
{
	return m_month;
}

int32 Time::Day() const
{
	return m_day;
}	

int32 Time::Hour() const
{
	return m_hour;
}

int32 Time::Minute() const
{
	return m_minute;
}

int32 Time::Second() const
{
	return m_second;
}

int64 Time::CpuClock() const
{
	return m_cpu_clock;
}

int32 Time::WeekDay() const
{
	return m_wday;
}

int32 Time::YeayDay() const
{
	return m_yday;
}

int64 Time::Seconds() const
{
	return m_utc_time;
}

int32 Time::Minutes() const
{
	return m_utc_time / 60;
}

int32 Time::Days() const
{
	return (m_utc_time + m_zone_second) / (24 * 3600);
}

int8 Time::Zone() const
{
	return m_zone_second / 3600;
}

int32 Time::ZoneSecond() const
{
	return m_zone_second;
}

string Time::AsString() const
{
	char buffer[BUF_MIN] = {0};
	snprintf( buffer, sizeof(buffer), "%4d-%02d-%02d %02d:%02d:%02d", m_year, m_month, m_day, m_hour, m_minute, m_second );
	return std::move( buffer );
}

void Time::Abjust( int64 time )
{
	if (time)
	{
		m_utc_time = time;
		m_is_tick = true;
		CasheClock();
		CasheTime();
	}
	else
		m_is_tick = false;
}

void Time::CasheClock()
{
#ifdef WIN32
	m_cpu_clock = static_cast< int64 >( clock() );
#elif UNIX
	timespec ts;
	clock_gettime( CLOCK_MONOTONIC, &ts );
	m_cpu_clock = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#endif
}

void Time::CasheTime()
{
	time_t time = static_cast< time_t >( m_utc_time );
	tm* local = localtime( &time );
	this->m_year		= local->tm_year + 1900;
	this->m_month		= local->tm_mon + 1;
	this->m_day		= local->tm_mday;
	this->m_hour		= local->tm_hour;
	this->m_minute	= local->tm_min;
	this->m_second	= local->tm_sec;
	this->m_wday		= local->tm_wday;
	this->m_yday		= local->tm_yday;
}
