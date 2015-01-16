#include "buffer.h"


FixedBuffer::FixedBuffer()
{
    bzore( m_data, sizeof(m_data) );
    m_curr = m_data;
}

FixedBuffer::~FixedBuffer()
{
    
}

const char* FixedBuffer::Data() const
{
    return m_data;
}

const char* End() const
{
    return m_data + sizeof(m_data);
}
