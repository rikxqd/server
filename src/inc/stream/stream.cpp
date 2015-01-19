#include "stream.h"

Stream::Stream()
{
}

Stream::~Stream()
{
}

Stream& Stream::operator << ( bool v )
{
	m_buffer.Append( (v ? "1"  :  "0") ,  1 );
	return *this;
}

Stream& Stream::operator << ( int16 v )
{
	return *this << static_cast< int32 >( v );
}

Stream& Stream::operator << ( uint16 v )
{
	return *this << static_cast< uint32 >( v );
}

Stream& Stream::operator << ( int32 v )
{
	char buf[16] = {0};
	int l = snprintf( buf, sizeof(buf), "%d", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( uint32 v )
{
	char buf[16] = {0};
	int l = snprintf( buf, sizeof(buf), "%u", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( int64 v )
{
	char buf[32] = {0};
	int l = snprintf( buf, sizeof(buf), "%lld", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( uint64 v )
{
	char buf[32] = {0};
	int l = snprintf( buf, sizeof(buf), "%llu", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( const void* v )
{
	char buf[32] = {0};
	int l = snprintf( buf, sizeof(buf), "%p", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( float v )
{
	char buf[16] = {0};
	int l = snprintf( buf, sizeof(buf), "%.8g", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( double v )
{
	char buf[32] = {0};
	int l = snprintf( buf, sizeof(buf), "%.16g", v );
	m_buffer.Append( buf,  l );
	return *this;
}

Stream& Stream::operator << ( char v ) 
{
	m_buffer.Append( &v, 1 );
	return *this;
}

Stream& Stream::operator << ( const char* v )
{
	if (v)
		m_buffer.Append( v, strlen( v ) );
	else
		m_buffer.Append( "(NULL)", 6 );
	return *this;
}

Stream& Stream::operator << ( const unsigned char* v )
{
	return *this << reinterpret_cast< const char* >( v );
}

Stream& Stream::operator << ( const std::string& v )
{
	m_buffer.Append( v.c_str(), v.size() );
	return *this;
}

const Stream::Buffer& Stream::Buf() const
{
	return m_buffer;
}

void Stream::Append(const char* v, int l) 
{
	m_buffer.Append( v, l );
}

void Stream::ResetBuffer()
{
	m_buffer.Reset();
}
