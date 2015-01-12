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

	void Debug( const char* desc, ... );
	void Info( const char* desc, ... );
	void Warning( const char* desc, ... );
	void Error( const char* desc, ... );
	void Fatal( const char* desc, ... );

private:
	string		m_name;
	ELogLevel	m_level;
};

#endif//_LOG_H_
