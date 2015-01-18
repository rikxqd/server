#ifndef _STR_FUN_H_
#define _STR_FUN_H_

#include <vector>

#include "public.h"


namespace StrFun
{
	typedef std::vector< std::string > Strings;
	void Split( Strings& list, const char* src, const char token );
}


#endif//_STR_FUN_H_
