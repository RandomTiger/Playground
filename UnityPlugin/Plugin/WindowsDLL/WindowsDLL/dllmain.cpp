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

	__declspec(dllexport) void TestFloatArray(float* pArray, int pSize)
	{
		for (int i = 0; i < pSize; i++)
		{
			pArray[i] = 1.1f;
		}
	}
}
