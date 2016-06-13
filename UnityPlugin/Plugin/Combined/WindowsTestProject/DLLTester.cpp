#include "../code/Flock/Flock.h"

int main()
{
	int entityCount = 100;
	int floatCount = entityCount * Flock::dataStride;
	float* data = new float[floatCount];
	static List<FlockEntity> m_Entities;

	for (int i = 0; i < entityCount; i++)
	{
		data[i*Flock::dataStride + 0] = 0;
		data[i*Flock::dataStride + 1] = 0;
		data[i*Flock::dataStride + 2] = 0;

		data[i*Flock::dataStride + 3] = 0;
		data[i*Flock::dataStride + 4] = 0;
		data[i*Flock::dataStride + 5] = 0;
		data[i*Flock::dataStride + 6] = 1;
	}

	Flock::FlockSetup(data, floatCount);
	Flock::FlockProcess(data, floatCount, 0.03f);

    return 0;
}

