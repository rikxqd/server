#ifndef _TIME_H_
#define _TIME_H_

#include "public.h"


class Time
{
public:
	Time();
	~Time();

	static void SleepMsec( int64 msec );

	void Refresh();

	int32 Year();
	int32 Month();
	int32 Day();
	int32 Hour();
	int32 Minute();
	int32 Second();
	int32 WeekDay();
	int32 YeayDay();
	int32 Seconds();
	int32 Minutes();

	void Abjust( int32 time = 0 );

protected:
	void CasheClock();
	void CasheTime();

private:
	int32	m_year;			//年（年份，如2011）
	int32	m_month;		//月（月份，1 -- 12）
	int32	m_day;			//日（日期，1 -- 31）
	int32	m_hour;			//时（小时，0 -- 23）
	int32	m_minute;		//分（分钟，0 -- 59）
	int32	m_second;		//秒（秒钟，0 -- 59）

	int32	m_wday;			//星期几（0，星期天；1，星期一 ...）
	int32	m_yday;			//今年的第几天

	int32	m_time;			//当前的UTC时间（非系统时间，内部计算的）
	int64	m_pass;			//系统启动的毫秒数

	bool	m_is_cumulation;//是否需要累加
	int64	m_cumulation;	//用于累加毫秒的累加器

	int32	m_zone_second;
};

#endif//_TIME_H_
