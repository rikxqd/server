#include "log_stream.h"

#include <fstream>


LogStream::LogStream()
{

}

LogStream::~LogStream()
{

}

void LogStream::Flush()
{
	ofstream file( "aa", ios::app );
	if ( file )
	{
		file << *this;
		file.close();
		Reset();
	}
}
