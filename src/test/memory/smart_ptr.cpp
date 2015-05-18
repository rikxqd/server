#include <stdio.h>
#include "utility/share_ptr.h"


class A : public RefCounter
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

typedef SharePtr<A> APtr;

int main( int argc, char* argv[] )
{
	APtr a = new A();
	printf("11111111111111111111\n");
	APtr b = a;
	printf("22222222222222222222\n");
	return 0;
}
