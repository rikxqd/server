#include <stdio.h>
#include "global.h"
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
	g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );
	{
		for ( uint32 i = 0 ; i < 100 ; ++i )
		{
			APtr a = new A();
			APtr& b = a;
			if ( i == 99 )
				g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );
		}
		g_log.Debug( "[%d][%d][%d]", g_count, g_new, g_delete );
	}

	return 0;
}
