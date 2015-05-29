#include <signal.h>
#include "public.h"
#include "xml.h"
#include "time/timer_manager.h"
#include "thread/thread_pool.h"
#include "framework/server_app.h"
#include "log/log_stream.h"


static void HandleSignal( int32 sigi )
{
	Thread::ThreadPool::Instance().Stop();
}

int32 main( int32 argc, char* argv[] )
{
	if ( !XML::Load() )
		exit(-1);

	if ( SIG_ERR == ::signal( SIGINT, HandleSignal ) || SIG_ERR == ::signal( SIGTERM, HandleSignal ) )
		exit(-1);

	Log::Instance().Stream( new LogStream( XML::log_file ) );
	Log::Instance().Name( XML::log_name );
	Log::Instance().Level( XML::log_level );

	Thread::ThreadPool::Instance().Start();
	ServerAppPtr server = new ServerApp();
	server->Init( XML::ip, XML::port );
	server->Start();
}
