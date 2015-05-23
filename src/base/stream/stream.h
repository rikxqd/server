#ifndef _STREAM_H_
#define _STREAM_H_

#include "buffer/buffer.h"
#include "log/source_file.h"


#define MAX_SIZE 2 << 10

class Stream
{
	typedef Buffer< MAX_SIZE > SBuffer;
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

	friend std::ostream& operator << ( std::ostream& r, Stream& s );
	friend std::ofstream& operator << ( std::ofstream& r, Stream& s );

	const SBuffer& Buf() const;
	const int32 Size() const;
	void Append( const char* v, int32 l );
	void Reset();

	virtual void Flush() = 0;
    
private:
	SBuffer m_buffer;
};

#endif//_STREAM_H_
