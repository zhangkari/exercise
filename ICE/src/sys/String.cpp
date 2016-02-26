#include <String.h>
#include <string.h>

String::String() : mBuffer(0), mLength(0)
{

}

String::String(const char* str)
{
	mLength = strlen(str);
	mBuffer = new char[mLength+1];
	memset(mBuffer, 0, mLength+1);
	strncpy(mBuffer, str, mLength);
}

String::String(String& s)
{
	mLength = s.GetLength();
	mBuffer = new char[mLength+1];
	memset(mBuffer, 0, mLength+1);
	strncpy(mBuffer, s.string(), mLength);
}

String::~String()
{
	if(mBuffer)
	{
		delete []mBuffer;
		mBuffer = 0;
	}
}

int String::GetLength()
{
	return mLength;
}

void String::SetLength(int length)
{
	this->mLength = length;
}

const char* String::string()
{
	return mBuffer;
}

bool String::Alloc(int n)
{
	this->mBuffer = new char[n];
	return true;
}

String& String::operator+(String& str)
{
	String* s = new String();
	s->SetLength(this->GetLength() + str.GetLength());
	s->Alloc(s->GetLength());
	char* p = s->mBuffer;
	strncpy(p,this->string(), this->GetLength());
	strncpy(p+this->GetLength(), str.string(), str.GetLength());
	
	return *s;
}
