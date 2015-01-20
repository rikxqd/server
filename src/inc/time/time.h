#ifndef _TIME_H_
#define _TIME_H_

class Time
{
public:
	Time();
	~Time();

private:
	uint32			m_year;			//年（年份，如2011）
	uint32			m_month;		//月（月份，1 -- 12）
	uint32			m_mday;		//日（日期，1 -- 31）
	uint32			m_hour;		//时（小时，0 -- 23）
	uint32			m_minute;		//分（分钟，0 -- 59）
	uint32			m_second;		//秒（秒钟，0 -- 59）
	uint32			m_wday;		//星期几（0，星期天；1，星期一 ...）
	uint32			m_yday;		//今年的第几天

	uint32			m_time;		//当前的UTC时间（非系统时间，内部计算的）
	uint64			m_run_time;	//根据CPU震荡周期保存的进程/系统启动的毫秒数

	uint64			m_Cumulation;		//用于累加毫秒的累加器
	bool			m_bIsCumulatino;	//标志是否需要累加
	uint32			m_TimeZoneSecond;	//计算时区
};

#endif//_TIME_H_
