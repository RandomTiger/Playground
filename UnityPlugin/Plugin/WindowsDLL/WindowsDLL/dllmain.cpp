extern "C"
{
	__declspec(dllexport) float add(float x, float y)
	{
		return x + y;
	}

	__declspec(dllexport) float mult(float x, float y)
	{
		return x * y;
	}

	__declspec(dllexport) int TestArrayOfInts(float* pArray, int pSize)
	{
		for (int i = 0; i < pSize; i++)
		{

		}
	}
}
