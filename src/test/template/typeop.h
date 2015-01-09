//typeop.hpp：根据传进去的类型，获取真正需要的类型
//可去掉类型中多余的&、const，例如避免在函数模板实参演绎时出现int& &或
//int const const之类的非法类型
#ifndef TYPEOP_HPP
#define TYPEOP_HPP
template<typename T>
class TypeOp{ //基本模板
public:
	typedef T ArgT; //参数类型：调用时的参数类型为T
	typedef T BareT; //裸类型：无引用符&，无限定符const
	typedef T const ConstT;
	typedef T& RefT;
	typedef T& RefBareT;
	typedef T const& RefConstT;
};
template<typename T>
class TypeOp<T const>{ //针对const类型的局部特化
public:
	typedef T const ArgT; //调用时的参数类型：有限定符const
	typedef T BareT;
	typedef T const ConstT;
	typedef T const& RefT;
	typedef T& RefBareT;
	typedef T const& RefConstT;
};
template<typename T>
class TypeOp<T&>{ //针对引用类型的局部特化
public:
	typedef T & ArgT; //调用时的参数类型：有限定符&
	typedef typename TypeOp<T>::BareT BareT;
	typedef T const ConstT;
	typedef T & RefT;
	typedef typename TypeOp<T>::BareT & RefBareT;
	typedef T const & RefConstT;
};
template<>
class TypeOp<void>{ //针对void的全局特化，因为指向void的引用或const类型不允许
public:
	typedef void ArgT; //调用时的参数类型：为void
	typedef void BareT;
	typedef void const ConstT;
	typedef void RefT;
	typedef void RefBareT;
	typedef void RefConstT;
};
#endif