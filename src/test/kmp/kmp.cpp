#include <iostream>
#include <string.h>

#include "str/str_func.h"


int main( int argc, char** argv )   
{
    const char* a = "abcdddwafswfwalomcp";
    const char* b = "wafswf";
    std::cout << StrFunc::KmpSearch( a, b ) << std::endl;

    char c[64] = {0};
    strncpy( c, a + StrFunc::KmpSearch( a, b ), strlen( b ) );
    std::cout << c << std::endl;
   return 0; 
}