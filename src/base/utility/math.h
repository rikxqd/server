#ifndef _MATH_H_
#define _MATH_H_

#include <vector>

#include "public.h"


namespace Math
{

int32 MCD( int32 n, int32 m );				// 最大公约数 max common divisor

int32 MCD( std::vector< int32 >& array );	// 最大公约数

}/* end of Math */

#endif//_MATH_H_
