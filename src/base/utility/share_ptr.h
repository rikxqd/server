#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

#include <iostream>
#include "utility/ref_counter.h"

/*
template<class T>
inline void IncRefCount(const T& obj)
{
	obj.IncRef();
};

template<class T>
inline void DecRefCount(const T& obj)
{
	obj.DecRef();
};*/

template<class T>
class ConstSharePtr
{
public:
	enum REF_TAG 
	{
		STEAL_REF, 
		NEW_REF,
	};
	
	ConstSharePtr( const T* obj = NULL, REF_TAG tag = ConstSharePtr::NEW_REF )
		: m_obj( obj )
	{
		if( obj && tag == ConstSharePtr::NEW_REF )
			m_obj->IncRef();
	}

	ConstSharePtr( const ConstSharePtr<T>& obj )
	{
		m_obj = obj.Get();
		if ( m_obj ) 
			m_obj->IncRef();
	}

	~ConstSharePtr()
	{
		if ( m_obj )
			m_obj->DecRef();

		m_obj = NULL;
	}
	
	void Clear()
	{
		if ( m_obj )
			m_obj->DecRef();
		
		m_obj = NULL;
	}
	
	const T* Get() const
	{
		return m_obj;
	}

	const T* operator()()
	{
		return m_obj;
	}

	ConstSharePtr<T>& operator=( const ConstSharePtr<T>& right )
	{
		if ( m_obj != right.Get() )
		{
			const T* old = m_obj;
			m_obj = right.Get();

			if (m_obj)
				m_obj->IncRef();

			if (old)
				old->DecRef();
		}

		return *this;
	}

	const T* operator->() const
	{
		return m_obj;
	}

	const T& operator*() const
	{
		return *m_obj;
	}

	/**
	 *	These functions return whether or not the input objects refer to the same
	 *	object.
	 */
	friend bool operator==( const ConstSharePtr<T>& A, const ConstSharePtr<T>& B )
	{
		return A.m_obj == B.m_obj;
	}

	friend bool operator==( const ConstSharePtr<T>& A, const T* B )
	{
		return A.m_obj == B;
	}

	friend bool operator==( const T* A, const ConstSharePtr<T>& B )
	{
		return A == B.m_obj;
	}

	/**
	 *	These functions return not or whether the input objects refer to the same
	 *	object.
	 */
	friend bool operator!=( const ConstSharePtr<T>& A, const ConstSharePtr<T>& B )
	{
		return A.m_obj != B.m_obj;
	}

	friend bool operator!=( const ConstSharePtr<T>& A, const T* B )
	{
		return A.m_obj != B;
	}

	friend bool operator!=( const T* A, const ConstSharePtr<T>& B )
	{
		return A != B.m_obj;
	}

	/**
	 *	These functions give an ordering on smart pointers so that they can be
	 *	placed in sorted containers.
	 */
	friend bool operator<( const ConstSharePtr<T>& A, const ConstSharePtr<T>& B )
	{
		return A.m_obj < B.m_obj;
	}

	friend bool operator<( const ConstSharePtr<T>& A, const T* B )
	{
		return A.m_obj < B;
	}

	friend bool operator<( const T* A, const ConstSharePtr<T>& B )
	{
		return A < B.m_obj;
	}

	/**
	 *	These functions give an ordering on smart pointers so that they can be
	 *	compared.
	 */
	friend bool operator>( const ConstSharePtr<T>& A, const ConstSharePtr<T>& B )
	{
		return A.m_obj > B.m_obj;
	}

	friend bool operator>( const ConstSharePtr<T>& A, const T* B )
	{
		return A.m_obj > B;
	}

	friend bool operator>( const T* A, const ConstSharePtr<T>& B )
	{
		return A > B.m_obj;
	}

	/**
	 *	This method returns whether or not this pointers points to anything.
	 */
	typedef const T * ConstSharePtr<T>::*unspecified_bool_type;
	operator unspecified_bool_type() const
	{
		return NULL == m_obj ? NULL : &ConstSharePtr<T>::m_obj;
	}
protected:
	const T* m_obj;
};

template <class T>
class SharePtr : public ConstSharePtr<T>
{
public:
	typedef ConstSharePtr<T> ConstProxy;
		
	SharePtr( T* obj = NULL, typename ConstProxy::REF_TAG tag = ConstProxy::NEW_REF )
		: ConstProxy( obj, tag )
	{
	}
	
	SharePtr( const SharePtr<T>& P ) 
		: ConstProxy( P )
	{
	}

	template<class DerivedType>
	SharePtr( ConstSharePtr<DerivedType>& dt ) :
		ConstProxy( dt.Get() )
	{
	}

	SharePtr<T>& operator=( const SharePtr<T>& P )
	{
		ConstProxy::operator=(P);
		return *this;
	}

	template<class DerivedType>
	SharePtr<T>& operator=( ConstSharePtr<DerivedType>& dt )
	{
		ConstProxy::operator=(dt.Get());
		return *this;
	}

	T * Get() const
	{
		return const_cast<T *>( this->m_obj );
	}

	T* operator->() const
	{
		return const_cast<T *>( this->m_obj );
	}

	T& operator*() const
	{
		return *const_cast<T *>( this->m_obj );
	}
};

#endif//_SMART_PTR_H_
