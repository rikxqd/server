#ifndef _STR_FUNC_H_
#define _STR_FUNC_H_

#include <vector>

#include "public.h"


namespace StrFunc
{

	typedef std::vector< std::string > Strings;
	void Split( Strings& list, const char* src, const char token );

	int32 KmpSearch( const char* src, const char* pattern );

}/* end of StrFunc */


#endif//_STR_FUNC_H_
