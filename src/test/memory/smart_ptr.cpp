#include <stdio.h>
#include "memory/smart_ptr.h"


class A : public RefCount
{
public:
	A()
	{
		printf("A()\n");
	}
	~A()
	{
		printf("~A()\n");
	}

private:
	int a;
};

typedef SmartPtr<A> APtr;

int main( int argc, char* argv[] )
{
	APtr a( new A() );
	printf("11111111111111111111\n");
	APtr b = a;
	printf("22222222222222222222\n");
	return 0;
}
