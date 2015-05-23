#include <stdio.h>

#include "time/time.h"


int main( int argc, char* argv[] )
{
	Time t;
	printf( "%4d-%02d-%02d %02d:%02d:%02d\n", t.Year(), t.Month(), t.Day(), t.Hour(), t.Minute(), t.Second() );

	printf( "%lld\n", t.Seconds() );

	printf( "zone:%d\n", t.Zone() );

	printf( "zone second:%d\n", t.ZoneSecond() );

	printf( "cup clock:%lld\n", t.CpuClock() );

	int64 time = Time::ToSecond( 2015, 1, 1, 0, 0, 0 );
	printf( "2015-1-1 00:00:00 : %lld", time );

	return 0;
}