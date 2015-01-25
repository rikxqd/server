#include <iostream>

#include "utility/math.h"


int main( int argc, char* argv[] )
{
	std::vector< int32 > array = { 147, 210, 315, 84 };

	cout << Math::MCD( array ) << endl;

	return 0;
}
