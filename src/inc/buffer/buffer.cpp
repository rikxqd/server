#include "buffer.h"


Buffer::Buffer( uint16 size )
	: m_size( size )
{
	m_head = new char[m_size];
	m_curr = m_head;
}

Buffer::~Buffer()
{

}