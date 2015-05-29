#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string.h>
#include <stdlib.h>

#include "define/integer.h"
#include "utility/non_copyable.h"


template< uint32 size >
class Buffer : NonCopyable
{
public:
    Buffer();
    ~Buffer();
    
    const char* Data() const;
    
    char* Current();
    
    uint32 Length() const;
    uint32 Avail() const;
    
    void Append( const char* buf, size_t len );
    
    void Reset();

protected:
    const char* End() const; 
    
private:
    char    m_data[size];
    char*   m_curr;
};

#include "buffer.inl"

#endif//_BUFFER_H_
