#define _USE_MATH_DEFINES
#include <math.h>

#include "Mathf.h"
#include "Ogre3D/Vector3.h"
#include <cstdlib>

float Mathf::Deg2Rad = 0.0174533f;
float Mathf::Rad2Deg = 57.2958f;
float Mathf::PI = (float) 3.14159265358979323846;

Vector3 Random::insideUnitSphere()
{
	float u1 = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
	float u2 = (rand() / (float)RAND_MAX);

	float r = (float)sqrt(1.0f - u1*u1);
	float theta = 2.0f* Mathf::PI *u2;

	return Vector3(r*(float)cos(theta), r*(float)sin(theta), u1);
}
