#include "global.h"

#include "log/log_stream.h"


LogStream g_log_stream;

Log g_log( "base", Log::LOG_ALL, g_log_stream );

Time g_time;
