#include "log.h"

#include <stdarg.h>


#define BUF_SIZE 2048

#define ENDL		"\033[0m" << std::endl

#define WHITE		std::cout << "\x1b[40;30m" 
#define RED			std::cout << "\x1b[40;31m"
#define GREEN		std::cout << "\x1b[40;32m"
#define YELLOW		std::cout << "\x1b[40;33m"
#define BLUE		std::cout << "\x1b[40;34m"
#define RED_WHITE	std::cout << "\x1b[41;30m"

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
	
	BLUE << "[" << m_name << "]:" << buffer << ENDL;
}

void Log::Info( const char* pattern, ... )
{
	if ( LOG_INFO > m_level )
		return;
	
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	GREEN << "[" << m_name << "]:" << buffer << ENDL;
}

void Log::Warning( const char* pattern, ... )
{
	if ( LOG_WARNING > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	YELLOW << "[" << m_name << "]:" << buffer << ENDL;
}

void Log::Error( const char* pattern, ... )
{
	if ( LOG_ERROR > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	RED << "[" << m_name << "]:" << buffer << ENDL;
}

void Log::Fatal( const char* pattern, ... )
{
	if ( LOG_FATAL > m_level )
		return;
		
	char buffer[BUF_SIZE] = {0};

	VA_BUFFER( buffer )
	
	RED_WHITE << "[" << m_name << "]:" << buffer << ENDL;
}
