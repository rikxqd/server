//isclassttest.cpp：测试IsClassT的实现
#include <iostream>
#include "template.h"

template<typename T>
void check()
{ //检查T是否是类类型：以模板实参方式传递类型
	if(IsClassT<T>::Yes)
	{
		std::cout<<" IsClassT(flag="<<IsClassT<T>::Yes<<")"<<std::endl;
	}
	else
	{
		std::cout<<" !IsClassT(flag="<<IsClassT<T>::Yes<<")"<<std::endl;
	}
}

template<typename T>
void checkT(T& a)
{  //检查T是否是类类型：以函数调用实参方式传递类型
	check<T>();
}

class MyClass
{ //类类型
};

struct MyStruct
{ //类类型
};

union MyUnion
{ //类类型
};

void myfunc()
{ //非类类型
}

enum E{ e1 }e; //非类类型

int main()
{
	std::cout<<"int: ";
	check<int>(); //非类类型
	
	std::cout<<"MyClass: ";
	check<MyClass>(); //类类型
	
	std::cout<<"MyStruct: ";
	MyStruct s;
	checkT(s); //类类型
	
	std::cout<<"MyUnion: ";
	check<MyUnion>(); //类类型
	
	std::cout<<"enum: ";
	checkT(e); //非类类型
	
	std::cout<<"myfunc():";
	checkT(myfunc); //非类类型
	
	return 0;
}