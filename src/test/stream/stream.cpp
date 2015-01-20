#include "log/log_stream.h"


int main( int argc, char* argv[] )
{
	bool v1 = false;
	int16 v2 = MIN_INT16;
	uint16 v3 = MAX_INT16;
	int32 v4 = MIN_INT32;
	uint32 v5 = MAX_INT32;
	int64 v6 = MIN_INT64;
	uint64 v7 = MAX_INT64;
	const void* v8 = &v1;
	float v9 = 3.1415926535898;
	double v10 = 3.14159265358985555555555;
	char v11 = 'A';
	const char* v12 = NULL;
	const unsigned char* v13 = reinterpret_cast< const unsigned char* >( "abcde" );
	const std::string v14 = "abcdef";

	int8 v15 = 0x7F;
	uint8 v16 = 255;

	LogStream s;

      s <<v1<<"\n"
		<<v2<<"\n"
		<<v3<<"\n"
		<<v4<<"\n"
		<<v5<<"\n"
		<<v6<<"\n"
		<<v7<<"\n"
		<<v8<<"\n"
		<<v9<<"\n"
		<<v10<<"\n"
		<<v11<<"\n"
		<<v12<<"\n"
		<<v13<<"\n"
		<<v14<<"\n"
		<<v15<<"\n"
		<<v16<<"\n";

	//cout << s << endl;

      return 0;
}
