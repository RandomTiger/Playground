#if WIN_DLL_TESTER
#include "..\..\..\WindowsDLLTester\stdafx.h"
#endif

#include "Vector3.h"
#include "Quaternion.h"

void assert(bool state) {}

const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);

Vector3 Vector3::operator *(const Quaternion& quat) const
{
	Vector3 result = *this;

	float num = quat.x * 2.0f;
	float num2 = quat.y * 2.0f;
	float num3 = quat.z * 2.0f;
	float num4 = quat.x * num;
	float num5 = quat.y * num2;
	float num6 = quat.z * num3;
	float num7 = quat.x * num2;
	float num8 = quat.x * num3;
	float num9 = quat.y * num3;
	float num10 = quat.w * num;
	float num11 = quat.w * num2;
	float num12 = quat.w * num3;

	result.x = (1.0f - (num5 + num6)) * x + (num7 - num12) * y + (num8 + num11) * z;
	result.y = (num7 + num12) * x + (1.0f - (num4 + num6)) * y + (num9 - num10) * z;
	result.z = (num8 - num11) * x + (num9 + num10) * y + (1.0f - (num4 + num5)) * z;
	return result;
}