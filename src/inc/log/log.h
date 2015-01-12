#ifndef _LOG_H_
#define _LOG_H_

#include "public.h"


class Log
{
	enum ELogLevel
	{
		LOG_FATAL,
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
		LOG_DEBUG,
		LOG_ALL,
	};
public:
	Log();
	explicit Log( const char* name, uint8 level = LOG_ALL );
	~Log();

	const char* Name() const;
	void Name( const char* name );
	
	uint8 Level() const;
	void Level( uint8 level );

	void Debug( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Info( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Warning( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Error( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );
	void Fatal( const char* pattern, ... ) __attribute__( ( format( printf, 2, 3 ) ) );

private:
	string		m_name;
	ELogLevel	m_level;
};

#endif//_LOG_H_
