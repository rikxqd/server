#ifndef _SOURCE_FILE_H_
#define _SOURCE_FILE_H_

#include "public.h"


class SourceFile
{
public:
	SourceFile( const char* name, int32 line );
	~SourceFile();

	const char* Name() const;
	const int32 Line() const;
	const int32 Size() const;

private:
	const char*	m_name;
	int32		m_line;
	int32		m_size;
};

#endif//_SOURCE_FILE_H_
