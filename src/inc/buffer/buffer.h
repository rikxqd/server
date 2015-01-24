#ifndef _BUFFER_H_
#define _BUFFER_H_

class Buffer : public NonCopyable
{
public:
	explicit Buffer( uint16 size );
	~Buffer();

private:
	const uint16	m_size;
	char const*		m_head;
	char*			m_curr;
};

#endif//_BUFFER_H_
