#ifndef _NOTIFY_HANDLER_H_
#define _NOTIFY_HANDLER_H_

#include "utility/share_ptr.h"


namespace Net
{

class InputNotifyHandler : public RefCounter
{
public:
	InputNotifyHandler(){};
	virtual ~InputNotifyHandler(){};
	virtual bool HandleInputNotify( int32 fd ) = 0;
};

typedef SharePtr<InputNotifyHandler> InputNotifyHandlerPtr;

class OutputNotifyHandler : public RefCounter
{
public:
	OutputNotifyHandler(){};
	virtual ~OutputNotifyHandler(){};
	virtual bool HandleOutputNotify( int32 fd ) = 0;
};

typedef SharePtr<OutputNotifyHandler> OutputNotifyHandlerPtr;

}/* end of Net */

#endif//_NOTIFY_HANDLER_H_
