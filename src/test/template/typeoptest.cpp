#include <iostream>
#include "define/typeop.h"


template< typename T >
void apply( typename TypeOp< T >::RefT arg, void (*func)( T ) )
{
	func( arg );
}

/*
template<typename T>
void apply(T& arg,void(*func)(T))
{
	func(arg);
}
*/

//类型为void(int)
void print( int a )
{ 
	std::cout<<a<<std::endl;
}

//类型为void(int&)
void incr( int& a )
{ 
	++a;
	std::cout<<a<<std::endl;
}

int main()
{
	int x=7;
	apply( x, print );
	apply( x, incr );
	return 0;
}