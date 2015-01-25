#ifndef _TIMER_H_
#define _TIMER_H_

#include "public.h"


class Timer : NonCopyable
{
	typedef void (*Handle)( Timer* owner, void* param );
	friend class TimerManager;
public:
	enum ETimerType
	{
		TIMER_ONCE		= 0, //一次型
		TIMER_CIRCLE	= 1, //循环型
	};

	enum ETimerStatus
	{
		TIMER_IDLE		= 0, //start前以及手动调用stop后的状态
		TIMER_ALIVE		= 1, //在manager的list里时候的状态
		TIMER_TIMEOUT	= 2, //超时后被移除的状态，循环型的没有
	};

	explicit Timer( uint32 interval, Handle handle, void* param, ETimerType type = TIMER_ONCE );
	~Timer();

	void Start();
	void Stop();
	void Reset( const uint32 interval );

private:
	uint32			m_interval;
	uint32			m_counter;
	ETimerType		m_type;
	ETimerStatus	m_status;
	Handle			m_handle;
	void*			m_param;
};

#endif//_TIMER_H_
