//isclasst.hpp：辨别类类型(class,struct,union)
#ifndef IS_CLASST_HPP
#define IS_CLASST_HPP

template<typename T>

class IsClassT
{  //确定某个类型是否为类类型
private:
	typedef char One;
	typedef struct
	{
		char a[2];
	}Two;
	
	template<typename C>
	static One test(int C::*); //C是类类型时使用这个版本，函数参数是一个C的成员指针
	
	template<typename C>
	static Two test(...); //C是非类类型时使用这个版本
	
public:
	enum { Yes=sizeof(test<T>(0))==1 }; //是类类型则Yes为1，不是类类型时Yes为0
	enum { No=!Yes };
};
#endif