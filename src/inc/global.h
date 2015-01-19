#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "log/log.h"
#include "log/source_file.h"


extern Log g_log;

#define DEBUG( buffer, ... )	\
	cout << SourceFile(__FILE__).Name() << ":" << __LINE__;	\
	g_log.Debug( buffer, ##__VA_ARGS__ )

#endif//_GLOBAL_H_
