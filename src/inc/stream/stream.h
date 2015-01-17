#ifndef _STREAM_H_
#define _STREAM_H_


#define MAX_SIZE 4000

class Stream
{
    typedef Stream Self;
    typedef FixedBuffer< MAX_SIZE > Buffer;
public:
    Stream();
    ~Stream();
    
private:
    Buffer m_buffer;
};

#endif//_STREAM_H_
