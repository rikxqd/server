#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "log/log.h"


extern Log g_log;

#define DEBUG( buffer, ... )	\
	cout << (strrchr( __FILE__, '/' ) + 1) << ":" << __LINE__;	\
	g_log.Debug( buffer, ##__VA_ARGS__ )

#endif//_GLOBAL_H_
