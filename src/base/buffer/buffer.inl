#include "buffer.h"

#include <string.h>
#include <assert.h>


template< uint32 size >
Buffer< size >::Buffer()
{
	memset( m_data, 0x00, sizeof(m_data) );
	m_curr = m_data;
}

template< uint32 size >
Buffer< size >::~Buffer()
{
}

template< uint32 size >
const char* Buffer< size >::Data() const
{
	return m_data;
}

template< uint32 size >
char* Buffer< size >::Current()
{
	return m_curr;
}

template< uint32 size >
uint32 Buffer< size >::Length() const
{
	assert( m_data <= m_curr );
	return static_cast< uint32 >( m_curr - m_data ); 
}

template< uint32 size >
uint32 Buffer< size >::Avail() const
{
	return static_cast< uint32 >( End() - m_curr );
}

template< uint32 size >
void Buffer< size >::Append( const char* buf, size_t len )
{
	if ( static_cast< size_t >( Avail() ) <= len )
		return;

	memcpy( m_curr, buf, len );
	m_curr += len;
}

template< uint32 size >
void Buffer< size >::Reset()
{
	memset( m_data, 0x00, sizeof(m_data) );
	m_curr = m_data;
}

template< uint32 size >
const char* Buffer< size >::End() const
{
	return m_data + sizeof(m_data);
}
