#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string.h>
#include <stdlib.h>

#include "public.h"


template< int32 size >
class FixedBuffer : public NonCopyable
{
public:
    FixedBuffer();
    ~FixedBuffer();
    
    const char* Data() const;
    
    char* Current();
    
    int32 Length() const;
    int32 Avail() const;
    
    void Append( const char* buf, size_t len );
    
    void Reset();

protected:
    const char* End() const; 
    
private:
    char    m_data[size];
    char*   m_curr;
};

#include "fixed_buffer.inl"

#endif//_BUFFER_H_
