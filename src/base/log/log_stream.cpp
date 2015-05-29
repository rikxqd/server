#include "log_stream.h"

#include <fstream>


LogStream::LogStream( const char* file_name )
	: m_file_name( file_name )
{
}

LogStream::~LogStream()
{
}

void LogStream::Flush()
{
	std::ofstream file( m_file_name.c_str(), std::ios::app );
	if ( file )
	{
		file << *this;
		file.close();
		Reset();
	}
}
