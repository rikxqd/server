#include <iostream>

#include "str/str_func.h"


int main( int argc, char** argv )   
{
    const char* a = "abcdddwafswfwalomcp";
    const char* b = "wafswf";
    std::cout << StrFunc::KmpSearch( a, b ) << std::endl;
   return 0; 
}