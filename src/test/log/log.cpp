#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    int i, j;
    for(i=40; i<48; i++)
        for(j=30; j<38; j++)
        {
            //printf("\x1b[%d;%dm%s\n\x1b[0m",i, j, "你好~");
            cout << "\x1b[" << i << ";" << j <<"m" << "你好~" << "\033[0m" << endl;
        }
    return 0;
}