#ifndef _LOG_H_
#define _LOG_H_

#include "public.h"

enum ELogLevel
{
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
};

class Logger
{
public:
	Logger(){}
	~Logger(){}

	const char* Name() const;
	void Name( const char* name );

	void Debug( const char* Format, ... );
	void Info( const char* Format, ... );
	void Warning( const char* Format, ... );
	void Error( const char* Format, ... );

private:
	string m_name;
};

#endif//_LOG_H_
