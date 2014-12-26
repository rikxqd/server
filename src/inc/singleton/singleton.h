#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#pragma once

template<typename T>
class Singleton
{
public:
	static T&	Instance( void ) {return m_pIntance;}

protected:
	Singleton( void ){}
	~Singleton( void ){}
	static T m_pIntance;
};

template<typename T>
T Singleton<T>::m_pIntance;

#endif//_SINGLETON_H_
