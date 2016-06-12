#include "Flock/Flock.h"

extern "C"
{
#ifdef _WINDOWS
__declspec(dllexport) 
#endif
	float add(float x, float y)
	{
		return x + y;
	}

#ifdef _WINDOWS
__declspec(dllexport)
#endif
	float sub(float x, float y)
	{
		return x - y;
	}

#ifdef _WINDOWS
__declspec(dllexport)
#endif
	float mult(float x, float y)
	{
		return x * y;
	}

#ifdef _WINDOWS
__declspec(dllexport)
#endif
	void TestFloatArray(float* pArray, int pSize)
	{
		for (int i = 0; i < pSize; i++)
		{
			pArray[i] = 1.1f;
		}
	}

#ifdef _WINDOWS
__declspec(dllexport)
#endif
	void FlockSetup(float* pArray, int pSize)
	{
		Flock::FlockSetup(pArray, pSize);
	}

#ifdef _WINDOWS
__declspec(dllexport)
#endif
	void ProcessFlock(float* pArray, int pSize, float deltaTime)
	{
		Flock::FlockProcess(pArray, pSize, deltaTime);
	}
}

