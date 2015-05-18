#ifndef _REF_COUNT_H_
#define _REF_COUNT_H_

#include <stdio.h>


class RefCount 
{
public:
	inline void IncRef() const
	{
		++m_ref_count;
		printf( "count %d\n", m_ref_count );
	}

	inline void DecRef() const
	{
		int curr = --m_ref_count;
		printf( "count %d\n", m_ref_count );
		//assert( 0 <= curr && " 0 > m_ref_count" );
		if ( 0 >= curr )
			OnRefOver();
	}

	virtual void OnRefOver() const
	{
		delete const_cast<RefCount*>( this );
	}

	void Count( int n )
	{
		m_ref_count = n;
	}

	int Count() const 
	{ 
		return m_ref_count; 
	}

protected:
	RefCount() 
		: m_ref_count( 0 ) 
	{
	}

	virtual ~RefCount() 
	{ 
		//assert( 0 == m_ref_count && "0 != m_ref_count!" ); 
	}

protected:
	volatile mutable int m_ref_count;
};

#endif//_REF_COUNT_H_
