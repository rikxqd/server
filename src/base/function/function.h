#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>


using namespace std;

template < typename R >
class Function;

template < typename R, typename T >
class Function< R (T) >
{
public:
    Function(){}
};

#endif//_FUNCTION_H_
