#ifndef _LOG_H_
#define _LOG_H_

#include "public.h"

class Logger
{
public:
	Logger(){}
	~Logger(){}

	const char* Name() const;
	void Name( const char* name );

	void Debug( const char* Format, ... );

private:
	string m_name;
};

#endif//_LOG_H_
