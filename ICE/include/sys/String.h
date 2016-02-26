#ifndef __STRING__H__
#define __STRING__H__

class String
{
	public:
		String();
		String(const char* str);
		String(String& s);
		~String();

		bool Alloc(int n);
		int GetLength();
		void SetLength(int length);
		const char* string();
		String& operator+(String& str);

	private:
		char* mBuffer;
		int mLength;
		
};

#endif
