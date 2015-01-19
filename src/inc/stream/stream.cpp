#include "stream.h"

Stream::Stream()
{
}

Stream::~Stream()
{
}

Self& Stream::operator << ( bool v )
{
    return *this;
}

Self& Stream::operator << ( int16 v )
{
    return *this;
}

Self& Stream::operator << ( uint16 v )
{
    return *this;
}

Self& Stream::operator << ( int32 v )
{
    return *this;
}

Self& Stream::operator << ( uint32 v )
{
    return *this;
}

Self& Stream::operator << ( int64 v )
{
    return *this;
}

Self& Stream::operator << ( uint64 v )
{
    return *this;
}

Self& Stream::operator << ( const void* v )
{
    return *this;
}

Self& Stream::operator << ( float v )
{
    return *this;
}

Self& Stream::operator << ( double v )
{
    return *this;
}

Self& Stream::operator << ( int8 v ) 
{
    return *this;
}

Self& Stream::operator << ( uint8 v ) 
{
    return *this;
}

Self& Stream::operator << ( const int8* v )
{
    return *this;
}

Self& Stream::operator << ( const uint8* v )
{
    return *this;
}

Self& Stream::operator << ( const std::string& v )
{
    return *this;
}

