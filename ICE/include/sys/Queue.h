#ifndef __QUEUE__H__
#define __QUEUE__H__

template <typename T>
class Queue
{
	public:
		Queue<T>(int size = STEP)
		{
			mCurSize = size;
			mBase = new T[mCurSize];
			mTail = 0;
			mHead = 0;
		}

		bool DeQueue(T& t)
		{
			if(!IsEmpty())
			{
				t = mBase[mHead++];
				return true;
			}
			return false;
		}

		bool InQueue(T t)
		{
			if(IsFull())
			{
				return false;
			}

			mBase[mTail++] = t;
			return true;
		}

		bool IsEmpty()
		{
			if(mTail <= mHead)
			{
				return true;
			}
			return false;
		}

		bool IsFull()
		{
			if(mTail - mHead >= mCurSize)
			{
				return true;
			}
			return false;
		}


	private:
		int mTail;
		int mHead;
		int mCurSize;
		T* mBase;
		const static int STEP;
};

template <class T>
const int Queue<T>::STEP = 64;

#endif
