#include "stream.h"

Stream::Stream()
{
}

Stream::~Stream()
{
}

Stream& Stream::operator << ( bool v )
{
    return *this;
}

Stream& Stream::operator << ( int16 v )
{
    return *this;
}

Stream& Stream::operator << ( uint16 v )
{
    return *this;
}

Stream& Stream::operator << ( int32 v )
{
    return *this;
}

Stream& Stream::operator << ( uint32 v )
{
    return *this;
}

Stream& Stream::operator << ( int64 v )
{
    return *this;
}

Stream& Stream::operator << ( uint64 v )
{
    return *this;
}

Stream& Stream::operator << ( const void* v )
{
    return *this;
}

Stream& Stream::operator << ( float v )
{
    return *this;
}

Stream& Stream::operator << ( double v )
{
    return *this;
}

Stream& Stream::operator << ( int8 v ) 
{
    return *this;
}

Stream& Stream::operator << ( uint8 v ) 
{
    return *this;
}

Stream& Stream::operator << ( const int8* v )
{
    return *this;
}

Stream& Stream::operator << ( const uint8* v )
{
    return *this;
}

Stream& Stream::operator << ( const std::string& v )
{
    return *this;
}

