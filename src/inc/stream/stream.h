#ifndef _STREAM_H_
#define _STREAM_H_

#include "buffer/fixed_buffer.h"


#define MAX_SIZE 4000

class Stream
{
    typedef Stream Self;
    typedef FixedBuffer< MAX_SIZE > Buffer;
public:
    Stream();
    ~Stream();
    
    Self& operator<<( bool v );
    Self& operator<<( int16 v );
    Self& operator<<( uint16 v );
    Self& operator<<( int32 v );
    Self& operator<<( uint32 v );
    Self& operator<<( int64 v );
    Self& operator<<( uint64 v );
    Self& operator<<( const void* v );
    Self& operator<<( float v );
    Self& operator<<( double v );
    Self& operator<<( char v ) ;
    Self& operator<<( const char* v );
    Self& operator<<( const unsigned char* v );
    Self& operator<<( const string& v );
    Self& operator<<( const std::string& v );
    
private:
    Buffer m_buffer;
};

#endif//_STREAM_H_
