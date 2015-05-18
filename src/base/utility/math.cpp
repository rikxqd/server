#include "math.h"


namespace Math
{

int32 MCD( int32 n, int32 m )
{
	if ( 0 == MIN( n, m ) )
		return MAX( n, m );

	return MCD( MIN( n, m ), (MAX( n, m ) % MIN( n, m )) );
	/*
	MAX( n, m )
	if ( n < m )
		n ^= m ^= n ^= m;

	if ( 0 == m ) 
		return n;
	return MCD( m, (n % m) );
	*/
}

int32 MCD( std::vector< int32 >& array )
{
	if ( 2 > array.size() )
		return 0;

	int32 mcd = array[0];
	for ( int32 i = 1, s = array.size() ; i < s ; ++i )
		mcd = MCD( mcd, array[i] );
	
	return mcd;
}

}/* end of Math */
