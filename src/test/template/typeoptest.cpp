//typeoptest.cpp:模板实参演绎错误(出现int& &)的测试
#include <iostream>
//#include "typeop.h"
/*
template<typename T>
void apply(typename TypeOp<T>::RefT arg,void (*func)(T)){
	func(arg);
}
*/
template<typename T>
void apply(T& arg,void(*func)(T)){
	func(arg);
}
void print(int a){ //类型为void(int)
	std::cout<<a<<std::endl;
}
void incr(int& a){ //类型为void(int&)
	++a;
}
int main(){
	int x=7;
	apply(x,print);
	//apply(x,incr);
	return 0;
}