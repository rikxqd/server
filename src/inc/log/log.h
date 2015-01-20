#ifndef _LOG_H_
#define _LOG_H_

#include "public.h"
#include "log/source_file.h"


class Stream;

class Log
{
public:
	enum ELogLevel
	{
		LOG_FATAL,
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
		LOG_DEBUG,
		LOG_ALL,
	};

	explicit Log( const char* name, uint8 level, Stream& stream );
	~Log();

	const char* Name() const;
	void Name( const char* name );
	
	uint8 Level() const;
	void Level( uint8 level );

	void Pattern( SourceFile file, uint32 line, uint8 level, const char* pattern, ... ) __attribute__( ( format( printf, 5, 6 ) ) );

	void Debug( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Info( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Warning( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Error( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Fatal( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );

private:
	string		m_name;
	ELogLevel	m_level;
	Stream&	m_stream;
};

#endif//_LOG_H_
