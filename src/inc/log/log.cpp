#include "log.h"

#include <stdarg.h>


#define BUF_SIZE 2048

#define WHITE( buffer )		std::cout << "\x1b[30m" << "[" << m_name << "]:" << buffer << "\033[0m" << std::endl
#define RED( buffer )		std::cout << "\x1b[31m" << "[" << m_name << "]:" << buffer << "\033[0m" << std::endl
#define GREEN( buffer )		std::cout << "\x1b[32m" << "[" << m_name << "]:" << buffer << "\033[0m" << std::endl
#define YELLOW( buffer )	std::cout << "\x1b[33m" << "[" << m_name << "]:" << buffer << "\033[0m" << std::endl
#define BLUE( buffer )		std::cout << "\x1b[34m" << "[" << m_name << "]:" << buffer << "\033[0m" << std::endl
#define RED_WHITE( buffer )	std::cout << "\x1b[41;30m" << "[" << m_name << "]:" << buffer << "\033[0m" << std::endl

#define VA_BUFFER( buffer )  \
	va_list list;	\
	va_start( list, pattern );	\
	int res = vsnprintf( (buffer), sizeof(buffer), pattern, list );	\
	va_end( list );

Log::Log()
	: m_name( "" )
	, m_level( LOG_ALL )
{
}

Log::Log( const char* name, uint8 level )
{
	Name( name );
	Level( (ELogLevel)level );
}
	
Log::~Log()
{
}

const char* Log::Name() const
{
	return m_name.c_str();
}

void Log::Name( const char* name )
{
	m_name = name;
}

uint8 Log::Level() const
{
	return m_level;
}

void Log::Level( uint8 level )
{
	m_level = (ELogLevel)level;
}

void Log::Debug( const char* pattern, ... )
{
	if ( LOG_DEBUG > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	BLUE( buffer );
}

void Log::Info( const char* pattern, ... )
{
	if ( LOG_INFO > m_level )
		return;
	
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	GREEN( buffer );
}

void Log::Warning( const char* pattern, ... )
{
	if ( LOG_WARNING > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	YELLOW( buffer );
}

void Log::Error( const char* pattern, ... )
{
	if ( LOG_ERROR > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	RED( buffer );
}

void Log::Fatal( const char* pattern, ... )
{
	if ( LOG_FATAL > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	RED_WHITE( buffer );
}
