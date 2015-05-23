#ifndef _COMMON_H_
#define _COMMON_H_

#include <vector>

#include "public.h"


namespace Common 
{
	typedef std::vector< std::string > Strings;
	void Split( Strings& list, const char* src, const char token );

	int32 KmpSearch( const char* src, const char* pattern );
}

#endif//_COMMON_H_
