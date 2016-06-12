#pragma once

#include "FlockEntity.h"

class Flock
{
public:
	static List<FlockEntity> m_Entities;
	static const int dataStride = 3 + 4;

	static void FlockSetup(float* pArray, int pSize);
	static void FlockProcess(float* pArray, int pSize, float deltaTime);
};
