#include <iostream>
#include <string.h>
#include <stdlib.h>


using namespace std;

void GetNextval(const char* p, int next[])  
{  
    int pLen = strlen(p);  
    next[0] = -1;  
    int k = -1;  
    int j = 0;  
    while (j < pLen - 1)  
    {   
        if (k == -1 || p[j] == p[k])  
        {  
            ++j;  
            ++k;  
            if (p[j] != p[k])  
                next[j] = k;
            else
                next[j] = next[k];  
        }  
        else  
            k = next[k];
    }  
}

int KmpSearch(const char* s, const char* p)  
{  
    int i = 0;  
    int j = 0;  
    int sLen = strlen(s);  
    int pLen = strlen(p);
    int* next = (int*)malloc( sizeof(int) * pLen );
    GetNextval(p, next);
    for ( int i = 0 ; i < pLen ; ++i )
        cout << *( next + i ) << endl;
    while (i < sLen && j < pLen)  
    {     
        if (j == -1 || s[i] == p[j])  
        {  
            i++;  
            j++;  
        }  
        else     
            j = next[j];
    } 
    free( next );
    if (j == pLen)  
        return i - j;  
    else  
        return -1;  
} 

int main( int argc, char** argv )   
{
    const char* a = "abcdddwafswfwalomcp";
    const char* b = "wafswf";
    std::cout << KmpSearch(a, b) << std::endl;
   return 0; 
}