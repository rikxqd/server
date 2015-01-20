#include "fixed_buffer.h"

#include <string.h>


template< int32 size >
FixedBuffer< size >::FixedBuffer()
{
	memset( m_data, 0x00, sizeof(m_data) );
	m_curr = m_data;
}

template< int32 size >
FixedBuffer< size >::~FixedBuffer()
{

}

template< int32 size >
const char* FixedBuffer< size >::Data() const
{
	return m_data;
}

template< int32 size >
char* FixedBuffer< size >::Current()
{
	return m_curr;
}

template< int32 size >
int32 FixedBuffer< size >::Length() const
{
	return static_cast< int32 >( m_curr - m_data ); 
}

template< int32 size >
int32 FixedBuffer< size >::Avail() const
{
	return static_cast<int32>( End() - m_curr );
}

template< int32 size >
void FixedBuffer< size >::Append( const char* buf, size_t len )
{
	if ( static_cast<size_t>( Avail() ) <= len )
		return;

	memcpy( m_curr, buf, len );
	m_curr += len;
}

template< int32 size >
void FixedBuffer< size >::Reset()
{
	m_curr = m_data;
	memset( m_data, 0x00, sizeof(m_data) );
}

template< int32 size >
const char* FixedBuffer< size >::End() const
{
	return m_data + sizeof(m_data);
}
