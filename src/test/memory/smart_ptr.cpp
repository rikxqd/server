#include <stdio.h>
#include "utility/share_ptr.h"


class A : public RefCounter
{
public:
	A()
	{
	}
	~A()
	{
	}

private:
	int a;
};

typedef SharePtr<A> APtr;

int main( int argc, char* argv[] )
{
	APtr a = new A();
	APtr b = a;
	return 0;
}
