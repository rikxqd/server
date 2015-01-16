#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "public.h"


template< int size >
class FixedBuffer : public NonCopyable
{
public:
    FixedBuffer();
    ~FixedBuffer();
    
    const char* Data() const;

protected:
    const char* End() const; 
    
private:
    char    m_data[size];
    char*   m_curr;
};

#endif//_BUFFER_H_
