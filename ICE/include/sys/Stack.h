#ifndef __STACK__H__
#define __STACK__H__

#include <string.h>

#define STEP_SIZE 64

template <typename T>
class Stack
{
	public:
		Stack();
		~Stack();
		bool Pop(T& t);
		void Push(T t);
		bool IsEmpty();
	private:
		T* mPtr;
		int mCurSize;
		int mMaxSize;
};

template <typename T>
Stack<T>::Stack() : mPtr(0), mCurSize(STEP_SIZE), mMaxSize(STEP_SIZE)
{
	mPtr = new T[mCurSize];
}

template <typename T>
Stack<T>::~Stack()
{
	delete []mPtr;
}

template <typename T>
bool Stack<T>::IsEmpty()
{
	if(mCurSize <= 0)
		return true;
	return false;
}

template <typename T>
bool Stack<T>::Pop(T& t)
{
	if(IsEmpty())
	{
		return false;
	}
	t = mPtr[--mCurSize];
	return true;
}

template <typename T>
void Stack<T>::Push(T t)
{
	if(mCurSize >= mMaxSize)
	{
		mMaxSize += STEP_SIZE;
		T* p = new T[mMaxSize];
		memmove(p, mPtr, sizeof(T) * mMaxSize);
		delete []mPtr;
		mPtr = p;
	}	

	mPtr[mCurSize++] = t;
}

#endif
