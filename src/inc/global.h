#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "log/log.h"
#include "log/source_file.h"
#include "log/log_stream.h"


extern Log g_log;
extern LogStream g_stream;

#define DEBUG( buffer, ... )	\
	g_log.Pattern( __FILE__, __LINE__, Log::LOG_DEBUG, buffer, ##__VA_ARGS__ )

#define INFO( buffer, ... )	\
	g_log.Pattern( __FILE__, __LINE__, Log::LOG_INFO, buffer, ##__VA_ARGS__ )

#define WARN( buffer, ... )	\
	g_log.Pattern( __FILE__, __LINE__, Log::LOG_WARNING, buffer, ##__VA_ARGS__ )

#define ERROR( buffer, ... )	\
	g_log.Pattern( __FILE__, __LINE__, Log::LOG_ERROR, buffer, ##__VA_ARGS__ )

#define FATAL( buffer, ... )	\
	g_log.Pattern( __FILE__, __LINE__, Log::LOG_FATAL, buffer, ##__VA_ARGS__ )


#endif//_GLOBAL_H_
