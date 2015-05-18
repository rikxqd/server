#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#pragma once

template< typename T >
class Singleton
{
public:
	static T&	Instance() 
	{ 
		if ( !m_intance )
			m_intance = new T;
		return *m_intance;
	}

protected:
	Singleton(){}
	~Singleton(){}
	
private:
	static T* m_intance;
};

template< typename T >
T* Singleton< T >::m_intance = new T;

#endif//_SINGLETON_H_
