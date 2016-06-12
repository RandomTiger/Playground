#include "Flock.h"

List<FlockEntity> Flock::m_Entities;

void Flock::FlockSetup(float* pArray, int pSize)
{
	int numEntities = pSize / dataStride;

	m_Entities.Values = new FlockEntity[numEntities];
	m_Entities.Count = numEntities;

	for (int i = 0; i < numEntities; i++)
	{
		m_Entities.Values[i].Start();

		m_Entities.Values[i].transform.position = Vector3(pArray[i*dataStride + 0], pArray[i*dataStride + 1], pArray[i*dataStride + 2]);
		m_Entities.Values[i].transform.rotation = Quaternion(pArray[i*dataStride + 3], pArray[i*dataStride + 4], pArray[i*dataStride + 5], pArray[i*dataStride + 6]);
	}
}

void Flock::FlockProcess(float* pArray, int pSize, float deltaTime)
{
	int numEntities = pSize / dataStride;
	Time::deltaTime = deltaTime;

	for (int i = 0; i < numEntities; i++)
	{
		m_Entities.Values[i].UpdateInternal(m_Entities, Vector3::zero);
	}
}
