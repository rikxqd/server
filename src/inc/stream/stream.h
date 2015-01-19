#ifndef _STREAM_H_
#define _STREAM_H_

#include "buffer/fixed_buffer.h"


#define MAX_SIZE 4000

class Stream
{
	typedef FixedBuffer< MAX_SIZE > Buffer;
public:
	Stream();
	~Stream();

	Stream& operator << ( bool v );
	Stream& operator << ( int16 v );
	Stream& operator << ( uint16 v );
	Stream& operator << ( int32 v );
	Stream& operator << ( uint32 v );
	Stream& operator << ( int64 v );
	Stream& operator << ( uint64 v );
	Stream& operator << ( const void* v );
	Stream& operator << ( float v );
	Stream& operator << ( double v );
	Stream& operator << ( char v ) ;
	Stream& operator << ( const char* v );
	Stream& operator << ( const unsigned char* v );
	Stream& operator << ( const std::string& v );

	const Buffer& Buf() const;
	void Append( const char* v, int32 l );
	void ResetBuffer();
    
private:
	Buffer m_buffer;
};

#endif//_STREAM_H_
