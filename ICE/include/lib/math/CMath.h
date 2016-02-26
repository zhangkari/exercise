

#ifndef __CMath__H__
#define __CMATH__H__

#include "ISimpleMath.h"
#include "IAdvMath.h"

class CMath : public ISimpleMath, public IAdvMath
{
	public:
		ECode QueryInterface(IID gid, void**ppv);
		void AddRef();
		void ReleaseRef();

		static ECode CreateInstance(CMath** math);
		int Add(int op1, int op2);
		int Pow(int a, int e);

	private:
		int mRef;
};

#endif
