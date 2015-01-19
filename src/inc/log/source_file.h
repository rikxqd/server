#ifndef _SOURCE_FILE_H_
#define _SOURCE_FILE_H_

#include "public.h"


class SourceFile
{
public:
	explicit SourceFile( const char* name );
	~SourceFile();

	friend std::ostream& operator << ( std::ostream& r, SourceFile& s );

	const char* Name() const;

private:
	const char*	m_name;
	int32		m_size;
};

#endif//_SOURCE_FILE_H_
