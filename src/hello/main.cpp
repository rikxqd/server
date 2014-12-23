#include <hello.h>

int main()
{
#ifdef DEBUG_LDH
      printf("DEBUG\n");
#endif

      HelloFunc();

      return 0;
}