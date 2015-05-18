#ifndef _LOG_STREAM_H_
#define _LOG_STREAM_H_

#include "stream/stream.h"


class LogStream : public Stream
{
public:
	LogStream();
	~LogStream();

	virtual void Flush();
};

#endif//_LOG_STREAM_H_
