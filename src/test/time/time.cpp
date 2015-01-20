#include <stdio.h>

#include "time/time.h"


int main( int argc, char* argv[] )
{
	Time t;
	printf( "%4d-%02d-%02d %02d:%02d:%02d\n", t.Year(), t.Month(), t.Day(), t.Hour(), t.Minute(), t.Second() );
	printf( "%d\n", t.Seconds() );
	printf( "%ld\n\n", time( 0 ) );
	t.Abjust( t.Seconds() );


	for ( uint32 i = 0 ; i < 3 ; ++i )
	{
		Time::SleepMsec( 6 * 1000 );
		t.Refresh();
		printf( "%4d-%02d-%02d %02d:%02d:%02d\n", t.Year(), t.Month(), t.Day(), t.Hour(), t.Minute(), t.Second() );
		printf( "%d\n", t.Seconds() );
		printf( "%ld\n\n", time( 0 ) );
	}

	return 0;
}