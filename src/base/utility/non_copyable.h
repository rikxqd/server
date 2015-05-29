#ifndef _NON_COPYABLE_H_
#define _NON_COPYABLE_H_


// ½ûÖ¹¿½±´
class NonCopyable  
{  
protected:  
	NonCopyable() {}
	~NonCopyable() {}  
private:
	NonCopyable( const NonCopyable& );  
	const NonCopyable& operator=( const NonCopyable& );  
};

#endif//_NON_COPYABLE_H_
