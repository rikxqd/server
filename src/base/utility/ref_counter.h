#ifndef _REF_COUNT_H_
#define _REF_COUNT_H_

#include "define/integer.h"


class RefCounter 
{
public:
	void IncRef() const;

	void DecRef() const;

	virtual void OnRefOver() const;

	void Count( int n );

	int Count() const;

protected:
	RefCounter();
	virtual ~RefCounter();

protected:
	volatile mutable int32 m_ref_count;
};

#endif//_REF_COUNT_H_
