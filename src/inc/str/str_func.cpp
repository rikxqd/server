#include "str_func.h"

#include <string.h>


static inline void GetNextVal( const char* pattern, int32 next[] )  
{  
	next[0] = -1;  
	int32 k = -1, j = 0, p_len = strlen( pattern );  
	while ( j < p_len - 1 )  
	{   
		if ( k == -1 || pattern[j] == pattern[k] )  
		{  
			++j;  
			++k;  
			if ( pattern[j] != pattern[k] )  
				next[j] = k;
			else
				next[j] = next[k];  
		}  
		else  
			k = next[k];
	}  
}

namespace StrFunc
{

int32 KmpSearch( const char* src, const char* pattern )
{
	int32 i = 0, j = 0, s_len = strlen( src ), p_len = strlen( pattern );
	if ( 0 == s_len || 0 == p_len )
		return -1;
	int32 next[p_len];
	memset( next, 0, p_len );
	GetNextVal( pattern, next );
	while ( i < s_len && j < p_len )  
	{     
		if ( j == -1 || src[i] == pattern[j] )  
		{  
			i++;  
			j++;  
		}  
		else     
			j = next[j];
	} 

	if ( j == p_len )  
		return i - j;  
	else  
		return -1; 
}

void Split( Strings& list, const char* src, const char token )
{
	if( NULL == src )
		return;

	list.clear();
	const char* begin = src;
	for ( const char* it = src ; true ; ++it )
	{
		if ( '\0' == *it )
		{
			if ( it != begin )
				list.push_back( std::string( begin , it - begin ) );

			return ;
		}
		else if ( token == *it )
		{
			if ( it != begin )
				list.push_back( std::string( begin , it - begin ) );

			begin = it + 1 ;
		}
	}
}

}/* end of StrFunc */
