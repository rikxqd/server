#include "source_file.h"

#include <string.h>
#include <iostream>


SourceFile::SourceFile( const char* name )
	: m_name( name )
{
	const char* sub = strrchr( name, '/' );
	if ( sub )
		m_name = sub + 1;

	m_size = static_cast< int32 >( strlen( m_name ) );
}

SourceFile::~SourceFile()
{

}

const char* SourceFile::Name() const
{
	return m_name;
}

const int32 SourceFile::Size() const
{
	return m_size;
}
