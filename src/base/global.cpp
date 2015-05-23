#include "global.h"

#include "log/log_stream.h"


LogStream				g_log_stream;
Log						g_log( "base", Log::LOG_ALL, g_log_stream );
Time					g_time;
Thread::ThreadPoolPtr	g_pool = new Thread::ThreadPool();
int32					g_count = 0;
int32					g_new = 0;
int32					g_delete = 0;
