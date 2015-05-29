#ifndef _LOG_STREAM_H_
#define _LOG_STREAM_H_

#include "stream/stream.h"


class LogStream : public Stream
{
public:
	LogStream( const char* file_name = "unknown" );
	~LogStream();

	virtual void Flush();

private:
	std::string m_file_name;
};

typedef SharePtr<LogStream> LogStreamPtr;

#endif//_LOG_STREAM_H_
