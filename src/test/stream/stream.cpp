#include "stream/stream.h"


int main( int argc, char* argv[] )
{
	bool v1 = false;
	int16 v2 = 65535;
	uint16 v3 = 65535;
	int32 v4 =4294967295;
	uint32 v5 = 4294967295;
	int64 v6 = 18446744073709551615U;
	uint64 v7 = 18446744073709551615U;
	const void* v8 = &v1;
	float v9 = 3.1415926535898;
	double v10 = 3.14159265358985555555555;
	char v11 = 'A';
	const char* v12 = NULL;
	const unsigned char* v13 = reinterpret_cast< const unsigned char* >( "abcdef" );
	const std::string v14 = "abcdefg";

	int8 v15 = 255;
	uint8 v16 = 255;

	Stream s;

      s <<v1<<"\n"<<v2<<"\n"<<v3<<"\n"<<v4<<"\n"<<v5<<"\n"<<v6<<"\n"<<v7<<"\n"<<v8<<"\n"<<v9<<"\n"<<v10<<"\n"<<v11<<"\n"<<v12<<"\n"<<v13<<"\n"<<v14<<"\n"<<v15<<"\n"<<v16;

	cout << s.Buf().Data() << endl;
      return 0;
}
