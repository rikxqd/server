#include "time_func.h"


namespace TimeFunc
{

int64 ToSecond( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second )
{
	tm tm_temp;
	tm_temp.tm_year	= year - 1900;
	tm_temp.tm_mon	= month - 1;
	tm_temp.tm_mday	= day;
	tm_temp.tm_hour	= hour;
	tm_temp.tm_min	= minute;
	tm_temp.tm_sec	= second;

	return static_cast< int64 >( mktime ( &tm_temp ) );
}

}/* end of TimeFunc */
