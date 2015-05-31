#include "ref_counter.h"
#include <assert.h>


RefCounter::RefCounter() 
	: m_ref_count( 0 ) 
{
}

RefCounter::~RefCounter() 
{ 
	assert( 0 == m_ref_count && "0 != m_ref_count!" );
}

void RefCounter::IncRef() const
{
	++m_ref_count;
}

void RefCounter::DecRef() const
{
	int curr = --m_ref_count;
	assert( 0 <= curr && " 0 > m_ref_count" );
	if ( 0 >= curr )
	{
		OnRefOver();
		delete const_cast<RefCounter*>( this );
	}
}

void RefCounter::OnRefOver() const
{
}

void RefCounter::Count( int n )
{
	m_ref_count = n;
}

int RefCounter::Count() const 
{ 
	return m_ref_count; 
}
