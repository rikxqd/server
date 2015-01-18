#include "str_fun.h"


namespace StrFun
{

void Split( Strings& list, const char* src, const char token )
{
	if( NULL == src )
		return;

	list.clear();
	const char* start = src;
	for ( const char * it = src ; true ; ++it )
	{
		if ( '\0' == * it)
		{
			if( it != start )
				list.push_back( std::string( start , it - start ) );

			return ;
		}
		else if( token == (*it) )
		{
			if( it != start )
				list.push_back( std::string( start , it - start ) );

			start = it + 1 ;
		}
	}
}

}
