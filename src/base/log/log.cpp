#include "log.h"
#include <stdarg.h>
#include "time/time.h"
#include "stream/stream.h"


#ifdef WIN32

#elif UNIX
	#define WHITE( buffer )		std::cout << "\x1b[40;30m" << (buffer) << "\033[0m" << std::endl
	#define RED( buffer )		std::cout << "\x1b[40;31m" << (buffer) << "\033[0m" << std::endl
	#define GREEN( buffer )		std::cout << "\x1b[40;32m" << (buffer) << "\033[0m" << std::endl
	#define YELLOW( buffer )	std::cout << "\x1b[40;33m" << (buffer) << "\033[0m" << std::endl
	#define BLUE( buffer )		std::cout << "\x1b[40;34m" << (buffer) << "\033[0m" << std::endl
	#define RED_WHITE( buffer )	std::cout << "\x1b[41;30m" << (buffer) << "\033[0m" << std::endl	
#endif

#define VA_BUFFER( buffer )  \
	va_list list;	\
	va_start( list, pattern );	\
	int res = vsnprintf( (buffer), sizeof(buffer), pattern, list );	\
	va_end( list );

static char s_level_name[Log::LOG_ALL][8] = { "Fatal", "Error", "Warn", "Info", "Debug" };

Log::Log()
	: m_name( "unknown" )
	, m_level( Log::LOG_ALL )
	, m_stream( NULL )
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

StreamPtr Log::Stream() const
{
	return m_stream;
}

void Log::Stream( StreamPtr stream )
{
	m_stream = stream;
}

void Log::Pattern( SourceFile file, ELogLevel level, const char* pattern, ... )
{
	if ( level > m_level )
		return;

	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )

	if ( m_stream )
	{
		Time now;
		m_stream->Format( "[%s][%s][%s][%s:%d] %s\n", 
			now.AsString().c_str(), 
			m_name.c_str(), 
			s_level_name[level], 
			file.Name(), 
			file.Line(), 
			buffer );

		m_stream->Flush();
	}
	else
	{
		switch ( level )
		{
		case LOG_DEBUG: Debug( "%s", buffer );break;
		case LOG_INFO: Info( "%s", buffer );break;
		case LOG_WARNING: Warning( "%s", buffer );break;
		case LOG_ERROR: Error( "%s", buffer );break;
		case LOG_FATAL: Fatal( "%s", buffer );break;
		default:break;
		}
	}
}

void Log::Debug( const char* pattern, ... )
{
	if ( LOG_DEBUG > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	GREEN( buffer );
}

void Log::Info( const char* pattern, ... )
{
	if ( LOG_INFO > m_level )
		return;
	
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	GREEN( buffer );
}

void Log::Warning( const char* pattern, ... )
{
	if ( LOG_WARNING > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	YELLOW( buffer );
}

void Log::Error( const char* pattern, ... )
{
	if ( LOG_ERROR > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	RED( buffer );
}

void Log::Fatal( const char* pattern, ... )
{
	if ( LOG_FATAL > m_level )
		return;
		
	char buffer[BUF_MED] = {0};

	VA_BUFFER( buffer )
	
	RED_WHITE( buffer );
}
