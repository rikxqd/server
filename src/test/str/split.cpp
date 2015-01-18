#include "string/str_fun.h"


int main()
{
	string a = "52dsadkja,dadwadha,dawdahdawda,dawhawh";
	cout << "a:" << a << endl;

	vector< string > list;
	StrFun::Split( list, a.c_str(), ',' );
	for ( int32 i = 0 ,s = list.size() ; i < s ; ++i )
	{
		cout << i << ":" << list[i] << endl;
	}
	return 0;
}
