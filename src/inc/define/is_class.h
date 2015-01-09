#ifndef _IS_CLASS_H_
#define _IS_CLASS_H_

//确定某个类型是否为类类型class,struct,union
template<typename T>
class ClassT
{  
private:
	typedef char One;
	typedef struct
	{
		char a[2];
	}Two;

	// C是类类型时使用这个版本，函数参数是一个C的成员指针
	template<typename C>
	static One Check(int C::*); 

	// C是非类类型时使用这个版本
	template<typename C>
	static Two Check(...); 

public:
	enum { Yes = sizeof(Check< T >( 0 )) == 1 }; //是类类型则Yes为1，不是类类型时Yes为0
	enum { No =! Yes };
};

//检查T是否是类类型：以模板实参方式传递类型
template< typename T >
bool IsClass()
{ 
	if( ClassT<T>::Yes )
		return true;

	return false;
}

//检查T是否是类类型：以函数调用实参方式传递类型
template< typename T >
bool IsClassT( T& a )
{  
	return IsClass< T >();
}

#endif//_IS_CLASS_H_
