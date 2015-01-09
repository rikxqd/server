#include <iostream>
#include "define/is_class.h"


using namespace std;

class MyClass
{
};

struct MyStruct
{
}my_struct;

union MyUnion
{
};

void MyFunc()
{
}

enum MyEnum
{ 
	Enum
}
my_enum;

int main()
{
	cout << "int: " << IsClass< int >() << endl; //非类类型
	
	cout << "MyClass: " << IsClass<MyClass>() << endl; //类类型

	cout << "my_struct: " << IsClassT( my_struct ) << endl; //类类型
	
	cout << "MyUnion: " << IsClass<MyUnion>() << endl; //类类型

	cout << "my_enum: " << IsClassT( my_enum ) << endl; //非类类型 只能传实例
	
	cout << "MyFunc():" << IsClassT( MyFunc ) << endl; //非类类型
	
	return 0;
}