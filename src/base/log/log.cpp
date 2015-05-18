#include "log.h"

#include <stdarg.h>

#include "global.h"
#include "stream/stream.h"
#include "time/time_func.h"


#ifdef WIN32

#elif UNIX
	#define WHITE			std::cout << "\x1b[40;30m" 
	#define RED			std::cout << "\x1b[40;31m"
	#define GREEN			std::cout << "\x1b[40;32m"
	#define YELLOW		std::cout << "\x1b[40;33m"
	#define BLUE			std::cout << "\x1b[40;34m"
	#define RED_WHITE	std::cout << "\x1b[41;30m"

	#define ENDL			"\033[0m" << std::endl
#endif

#define VA_BUFFER( buffer )  \
	va_list list;	\
	va_start( list, pattern );	\
	int res = vsnprintf( (buffer), sizeof(buffer), pattern, list );	\
	va_end( list );

static char s_level_name[Log::LOG_ALL][8] = { "Fatal", "Error", "Warn", "Info", "Debug" };

Log::Log( const char* name, uint8 level, Stream& stream )
	: m_name( name )
	, m_level( (ELogLevel)level )
	, m_stream( stream )
{
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

void Log::Pattern( SourceFile file, ELogLevel level, const char* pattern, ... )
{
	if ( level > m_level )
		return;

	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )

	m_stream 
	<< "[" << g_time.AsString() << "][" 
	<< m_name << "][" 
	<< s_level_name[level] << "][" 
	<< file.Name() << ':' << file.Line()  << "]"
	<< " " << buffer << "\n";

	m_stream.Flush();
}

void Log::Debug( const char* pattern, ... )
{
	if ( LOG_DEBUG > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	GREEN << buffer << ENDL;
}

void Log::Info( const char* pattern, ... )
{
	if ( LOG_INFO > m_level )
		return;
	
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	GREEN << buffer << ENDL;
}

void Log::Warning( const char* pattern, ... )
{
	if ( LOG_WARNING > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	YELLOW << buffer << ENDL;
}

void Log::Error( const char* pattern, ... )
{
	if ( LOG_ERROR > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	RED << buffer << ENDL;
}

void Log::Fatal( const char* pattern, ... )
{
	if ( LOG_FATAL > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	RED_WHITE << buffer << ENDL;
}
