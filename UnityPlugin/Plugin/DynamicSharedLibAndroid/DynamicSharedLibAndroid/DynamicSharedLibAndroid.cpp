extern "C" 
{
	float add(float x, float y)
	{
		return x + y;
	}

	float mult(float x, float y)
	{
		return x * y;
	}

	void TestFloatArray(float* pArray, int pSize)
	{
		for (int i = 0; i < pSize; i++)
		{
			pArray[i] = 1.1f;
		}
	}
}
