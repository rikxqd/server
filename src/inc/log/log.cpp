#include "log.h"

#include <stdarg.h>


#define BUF_SIZE 2048

const char* Logger::Name() const
{
	return m_name.c_str();
}

void Logger::Name( const char* name )
{
	m_name = name;
}

void Logger::Debug( const char* Format, ... )
{
	char buffer[BUF_SIZE] = {0};

	va_list list;
	va_start( list,Format );
	int retval = vsnprintf( buffer, sizeof(buffer), Format, list );
	buffer[sizeof(buffer) - 1] = 0 ;
	va_end( list );
}
