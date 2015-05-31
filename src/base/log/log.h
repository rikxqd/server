#ifndef _LOG_H_
#define _LOG_H_

#include "define/integer.h"
#include "log/source_file.h"
#include "singleton/singleton.h"
#include "stream/stream.h"


class Log : public Singleton<Log>
{
	friend class Singleton<Log>;
	Log();
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
	~Log();

	const char* Name() const;
	void Name( const char* name );
	
	uint8 Level() const;
	void Level( uint8 level );

	StreamPtr Stream() const;
	void Stream( StreamPtr stream );

#ifdef WIN32
	void Pattern(SourceFile file, ELogLevel level, const char* pattern, ...);
	void Debug( const char* pattern, ... );
	void Info( const char* pattern, ... );
	void Warning( const char* pattern, ... );
	void Error( const char* pattern, ... );
	void Fatal( const char* pattern, ... );
#elif UNIX
	void Pattern( SourceFile file, ELogLevel level, const char* pattern, ... ) __attribute__( ( format( printf, 4, 5 ) ) );
	void Debug( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Info( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Warning( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Error( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Fatal( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
#endif

private:
	std::string	m_name;
	ELogLevel	m_level;
	StreamPtr	m_stream;
};

#endif//_LOG_H_
