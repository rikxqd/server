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
		TIMER_TYPE_ONCE		= 0, //һ����
		TIMER_TYPE_CIRCLE	= 1, //ѭ����
	};

	enum ETimerStatus
	{
		TIMER_STATUS_IDLE		= 0, //startǰ�Լ��ֶ�����stop���״̬
		TIMER_STATUS_ALIVE		= 1, //��manager��list��ʱ���״̬
		TIMER_STATUS_TIMEOUT	= 2, //��ʱ���Ƴ���״̬��ѭ���͵�û��
	};

	explicit Timer( uint32 interval, Handle handle, void* param = NULL, ETimerType type = TIMER_TYPE_ONCE );
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