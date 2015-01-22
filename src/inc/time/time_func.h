#ifndef _TIME_FUNC_H_
#define _TIME_FUNC_H_

#include "public.h"
#include "time/time.h"


namespace TimeFunc
{

	int64 ToSecond( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second );

	string AsString( Time& t );

}/* end of TimeFunc */

#endif//_TIME_FUNC_H_
